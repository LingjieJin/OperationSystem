<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
        <%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
            <!DOCTYPE html>
            <html>

            <head>
                <base href="<%=basePath%>">
                <meta charset="UTF-8">
                <title>订单详情界面</title>
                <link rel="stylesheet" href="static/css/bootstrap.min.css" />
                <script src="js/jquery.min.js"></script>
                <style>
                    body {
                        background-color: #f7f7f7;
                        /* 背景色 */
                    }
                    
                    .panel {
                        margin-top: 20px;
                        /* 面板顶部间距 */
                    }
                    
                    .panel-header {
                        background-color: #007bff;
                        /* 面板头背景色 */
                        color: #fff;
                        /* 面板头文字颜色 */
                    }
                    
                    th {
                        background-color: #007bff;
                        /* 表头背景色 */
                        color: #fff;
                        /* 表头文字颜色 */
                    }
                    
                    .table tr:nth-child(even) {
                        background-color: #f2f2f2;
                        /* 表格偶数行背景 */
                    }
                    
                    .pagination {
                        margin: 20px 0;
                        /* 分页导航上下间距 */
                    }
                    
                    .pagination li a {
                        padding: 8px 12px;
                        /* 分页链接内边距 */
                        margin: 0 2px;
                        /* 分页链接间距 */
                        background-color: #007bff;
                        /* 分页链接背景色 */
                        color: white;
                        /* 分页链接文字颜色 */
                        border-radius: 5px;
                        /* 分页链接圆角 */
                    }
                    
                    .pagination li a:hover {
                        background-color: #0056b3;
                        /* 分页链接悬停背景色 */
                    }
                    
                    .error-message {
                        color: red;
                        /* 错误信息颜色 */
                        margin-top: 10px;
                        /* 错误信息顶部间距 */
                    }
                </style>
            </head>

            <body>
                <!-- 加载header.jsp -->
                <div>
                    <jsp:include page="user_Header.jsp"></jsp:include>
                </div>
                <br><br><br>
                <div class="container">
                    <div class="panel panel-primary">
                        <div class="panel-heading">
                            <h3 class="panel-title">订单列表</h3>
                        </div>
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-bordered table-hover">
                                    <thead>
                                        <tr>
                                        	<th>订单 ID</th>
                                            <th>商品名称</th>
                                        </tr>
                                    </thead>
                                    <tbody class="text-center">
                                            <c:forEach items="${product_order_list}" var="productOrder">
                                                <tr>
                                                	<td>${productOrder.order_id}</td>
                                                    <td>${productOrder.product_name}</td>
                                                </tr>
                                            </c:forEach>
                                            
                                    </tbody>
                                </table>
                            </div>
                        </div>

                    </div>
                </div>
            </body>

            </html>