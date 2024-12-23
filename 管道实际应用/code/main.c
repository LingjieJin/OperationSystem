#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <fcntl.h> 
#include <ctype.h>

#define MAX_WORD_LEN 100 
#define MAX_UNIQUES 1000

#define NUM_MAPPERS 8
#define NUM_REDUCERS 2

typedef struct {
    char* word;
    int count;
} count;

/**
 * 比较两个count结构体的count成员的值
 * 本函数用于qsort等函数的比较操作，以决定元素的排序顺序
 * 
 * @param p1 指向第一个count结构体的指针
 * @param p2 指向第二个count结构体的指针
 * 
 * @return 返回值小于、等于、大于0，分别表示第一个count小于、等于、大于第二个count
 *         这里的比较是基于count成员的值进行的
 */
int cmp_count(const void* p1, const void* p2) {
    // 将void指针转换为count类型的指针，并获取count成员的值
    int c1 = ((count*)p1)->count;
    int c2 = ((count*)p2)->count;
    
    // 比较两个count值
    if (c1 == c2) return 0; // 如果相等，返回0
    if (c1 < c2) return 1;  // 如果第一个小于第二个，返回1
    return -1;              // 如果第一个大于第二个，返回-1
}
int cmp_count(const void* p1, const void* p2) {
    int c1 = ((count*)p1)->count;
    int c2 = ((count*)p2)->count;
    if (c1 == c2) return 0;
    if (c1 < c2) return 1;
    return -1;
}

// 大小写转换
void toLowerCase(char *str) {  
    while (*str) {  
        *str = tolower((unsigned char)*str);
        str++; 
    }  
}  

//管道全局变量
static int mapper_pid[NUM_MAPPERS];  
static int reducer_pid[NUM_REDUCERS];
static int masterToMapper_pipes[NUM_MAPPERS][2];
static int mapperToReducer_pipes[NUM_REDUCERS][2];
static int reducerToMaster_pipes[NUM_REDUCERS][2]; 

void mapper(int pipe_fd) {
    // 子进程管道控制     
    close(masterToMapper_pipes[pipe_fd][1]); // 关闭写端   
    for (int i = 0; i < NUM_MAPPERS; i++) {  
        if (i != pipe_fd) {  
            close(masterToMapper_pipes[i][0]);  // 关闭其他管道的读端  
            close(masterToMapper_pipes[i][1]);  // 关闭其他管道的写端  
        }  
    }

    int reducer_index = pipe_fd % NUM_REDUCERS;
    for (int i = 0; i < NUM_REDUCERS; i++) {  
        close(mapperToReducer_pipes[i][0]); 
        if (i != reducer_index) {   
            close(mapperToReducer_pipes[i][1]);  // 关闭其他管道的写端  
        }    
    }

    for (int i = 0; i < NUM_REDUCERS; i++) {  
        close(reducerToMaster_pipes[i][0]); 
        close(reducerToMaster_pipes[i][1]); 
    } 

    // mapper读取word
    char word[255],letter[1];
    int status, w_status;
    int currentIdx;

    while ((status = read(masterToMapper_pipes[pipe_fd][0], letter, 1)) > 0)
    {
        currentIdx = 0;
        while (*letter != '\0')
        {
            // 分隔符
            if (*letter == '\n' || *letter == ' ' || *letter == '?' || 
                *letter == '!' || *letter == '@' || *letter == '~' || *letter == '#' ||
                *letter == '$' || *letter == '%' || *letter == '^' || *letter == '&' || *letter == '*' ||
                 *letter == '_' ||
                 *letter == '[' || *letter == ']' ||
               *letter == '>' || *letter == '\r' || 
                *letter == '\'' || *letter == '`' || *letter == ';' )
            {
                break;
            }

            // 判断字符范围
            if ((*letter < 'a' || *letter > 'z') && (*letter < 'A' || *letter > 'Z') && (*letter < '0' || *letter > '9'))
            {
                status = read(masterToMapper_pipes[pipe_fd][0], letter, 1);
                continue;
            }

            word[currentIdx++] = *letter;
            status = read(masterToMapper_pipes[pipe_fd][0], letter, 1);
        }

        // 单个数字不属于word范围
        if(currentIdx == 1)
        {
            if ((word[0] >= '0' && word[0] <= '9'))
            {
                continue;
            }
        }

        word[currentIdx] = '\n';
        word[currentIdx+1] = '\0';
        toLowerCase(word);
        write(mapperToReducer_pipes[reducer_index][1], word, strlen(word));
    }

    close(masterToMapper_pipes[pipe_fd][0]);
    close(mapperToReducer_pipes[reducer_index][1]);

    exit(0);  
}  

void reducer(int pipe_fd) { 
    // 子进程管道配置    
    for (int i = 0; i < NUM_REDUCERS; i++)
    {
        close(mapperToReducer_pipes[pipe_fd][1]); // 关闭写端
        if (i != pipe_fd)
        {
            close(mapperToReducer_pipes[i][0]); // 关闭其他管道的读端
            close(mapperToReducer_pipes[i][1]); // 关闭其他管道的写端
        }
    }

    for (int i = 0; i < NUM_MAPPERS; i++)
    {
        close(reducerToMaster_pipes[i][0]); // 关闭读端
        if (i != pipe_fd)
        {
            close(reducerToMaster_pipes[i][0]); // 不需要读取
            close(reducerToMaster_pipes[i][1]); // 不需要写入
        }
    }

    for (int i = 0; i < NUM_MAPPERS; i++)
    {
        close(masterToMapper_pipes[i][0]); // 不需要读取
        close(masterToMapper_pipes[i][1]); // 不需要写入
    }

    // 读取word
    char word[255],letter[1];
    int status, w_status;
    int currentIdx;

    count words[MAX_UNIQUES];
    int num_words = 0;
    while ((status = read(mapperToReducer_pipes[pipe_fd][0], letter, 1)) > 0)
    {
        currentIdx = 0;
        while (*letter != '\0')
        {
            if(*letter == ' ' || *letter == '\n')
                break;
            word[currentIdx++] = *letter;
            status = read(mapperToReducer_pipes[pipe_fd][0], letter, 1);
        }
        word[currentIdx] = '\0';

        // 判断当前word是否已存在
        int found = 0;
        for (int i = 0; i < num_words; i++) {
            if (strcmp(words[i].word, word) == 0) {
                found = 1;
                words[i].count ++;
                break;
            }
        }

        if (!found && num_words < MAX_UNIQUES) {
            words[num_words].word = strdup(word);
            words[num_words].count = 1;
            num_words++;
        }
    }
    qsort(words, num_words, sizeof(count), cmp_count);

    // 组合所有单词与计数为字符串 
    char buffer[MAX_UNIQUES * (MAX_WORD_LEN + 20)] = ""; 
    char temp[MAX_WORD_LEN + 20]; 
    for (int i = 0; i < num_words; i++) {  
        snprintf(temp, sizeof(temp), "%s:%d\n", words[i].word, words[i].count);  
        strncat(buffer, temp, sizeof(buffer) - strlen(buffer) - 1);  
    } 
    // 写入组合好的字符串到管道
    write(reducerToMaster_pipes[pipe_fd][1], buffer, strlen(buffer));  

    close(mapperToReducer_pipes[pipe_fd][0]); 
    close(reducerToMaster_pipes[pipe_fd][1]); 
 
    exit(0);  
}  

int main(int argc, char *argv[]) { 
    // 创建masterToMapper的管道  
    for (int i = 0; i < NUM_MAPPERS; i++) {  
        if (pipe(masterToMapper_pipes[i]) == -1) {
            perror("Failed to create mapper pipes");
            return 1;
        }  
    }  

    // 创建mapperToReducer的管道  
    for (int i = 0; i < NUM_REDUCERS; i++) { 
        if (pipe(mapperToReducer_pipes[i]) == -1) {
            perror("Failed to create reducer pipes");
            return 1;
        }  
    } 

    // 创建reducerToMaster的管道 
    for (int i = 0; i < NUM_REDUCERS; i++) { 
        if (pipe(reducerToMaster_pipes[i]) == -1) {
            perror("Failed to create reducer pipes");
            return 1;
        }  
    } 

    // 创建子进程
    for (int i = 0; i < NUM_MAPPERS; i++) {  
        if ((mapper_pid[i] = fork()) == 0) {
            mapper(i);  
        }
        close(masterToMapper_pipes[i][0]); // 父进程关闭读端    
    } 

    for (int i = 0; i < NUM_REDUCERS; i++) {  
        if ((reducer_pid[i] = fork()) == 0) {   
            reducer(i);  
        } 
        close(mapperToReducer_pipes[i][0]); 
        close(mapperToReducer_pipes[i][1]);
        close(reducerToMaster_pipes[i][1]); // 父进程关闭写端
    }  

    // 主进程读取流并发送到Mapper  
    char *readline = NULL;
    char *writeline = NULL;
    size_t len = 0;
    ssize_t line_len;
    int mapper_index = 0;
    while ((line_len = getline(&readline, &len, stdin)) != -1) {

        if(line_len == 1 && readline[line_len-1] == '\n')
        {
            continue;
        }

        // 检查是否缺少换行符，确保每行都以 '\n' 结尾
        if (readline[line_len - 1] != '\n')
        {
            writeline = calloc(line_len+1,sizeof(char));
            memcpy(writeline,readline,line_len);
            writeline[line_len] = '\n';
            writeline[line_len+1] = '\0';
            line_len +=1;

            if (write(masterToMapper_pipes[mapper_index][1], writeline, line_len) == -1)
            {
                perror("Error writing to pipe");
                return 1;
            }

            free(writeline);
            writeline = NULL;
        }
        else
        {
            if (write(masterToMapper_pipes[mapper_index][1], readline, line_len) == -1)
            {
                perror("Error writing to pipe");
                return 1;
            }
        }

        mapper_index = (mapper_index + 1) % NUM_MAPPERS;
        usleep(100);
    }
    free(readline);
    readline = NULL;

    // 关闭所有 Mapper 的写端
    for (int i = 0; i < NUM_MAPPERS; i++)
    {
        close(masterToMapper_pipes[i][1]);
    }

    // 等待 Mapper 进程完成
    for (int i = 0; i < NUM_MAPPERS; i++)
    {
        waitpid(mapper_pid[i], NULL, 0);
    }

    // 主进程获取所有的reducer结果
    count words[MAX_UNIQUES]; 
    int num_words=0;

    for (int i = 0; i < NUM_REDUCERS; i++) { 
        // 定义一个大缓冲区存放所有数据  
        char buffer[4096] = ""; 
        ssize_t bytes_read;
        // 一次性读取完整的数据
        bytes_read = read(reducerToMaster_pipes[i][0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0'; // 确保字符串结束
            // 解析数据：逐行分解
            char *line = strtok(buffer, "\n");
            while (line != NULL)
            {
                char word[MAX_WORD_LEN];
                int count;
                // 对每行解析格式：word:count
                if (sscanf(line, "%[^:]:%d", word, &count) == 2)
                {
                    int found = 0;
                    for (int i = 0; i < num_words; i++)
                    {
                        if (strcmp(words[i].word, word) == 0)
                        {
                            found = 1;
                            words[i].count += count;
                            break;
                        }
                    }

                    if (!found && num_words < MAX_UNIQUES)
                    {
                        words[num_words].word = strdup(word);
                        words[num_words].count = count;
                        num_words++;
                    }
                }

                // 解析下一行
                line = strtok(NULL, "\n");
            }
        }
        else if (bytes_read == 0)
        {
            // fprintf(stderr, "Reducer pipe %d EOF.\n", i);
        }
        else
        {
            perror("Error reading from reducer pipe");
            exit(1);
        }
    }

    // 输出所有的word结果
    for (int i = 0; i < num_words; i++)
    {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    // 关闭reducerToMaster管道
    for (int i = 0; i < NUM_REDUCERS; i++) { 
        close(reducerToMaster_pipes[i][0]);  
    }  

    // 等待所有Reducer完成  
    for (int i = 0; i < NUM_REDUCERS; i++)
    {
        // fprintf(stderr, "Parent waiting for mapper %d\n", i);
        waitpid(reducer_pid[i], NULL, 0);
    }

    return 0;  
}