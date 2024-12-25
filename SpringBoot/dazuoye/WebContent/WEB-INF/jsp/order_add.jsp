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
    <title>商品管理界面</title>  
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
            background-color: #000; /* 设置表头背景色为黑色 */  
            color: #fff; /* 设置表头文字颜色为白色 */  
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
        
        .product-table {  
            width: 100%;  
            border-collapse: collapse;  
            margin-top: 10px;  
        }  
        
        .product-table th, .product-table td {  
            padding: 15px;  
            text-align: center;  
            border: 1px solid #ddd;  
        }  
        
        .product-table th {  
            background-color: #000; /* 表头背景改为黑色 */  
            color: #fff; /* 表头文字颜色 */  
        }  
        
        .product-row:hover {  
            background-color: #f1f1f1; /* 行悬停效果 */  
        }  
        
        .scroll-container {  
            max-height: 400px;  
            overflow-y: auto;  
            border: 1px solid #ccc;  
            border-radius: 5px; /* 圆角效果 */  
            padding: 10px;  
        }  
        
        .btn-success {  
            background-color: #28a745;  
            color: white;  
            padding: 10px 20px;  
            border: none;  
            border-radius: 5px; /* 圆角按钮 */  
            cursor: pointer;  
            text-decoration: none; /* 去掉下划线 */  
        }  
        
        .btn-success:hover {  
            background-color: #218838; /* 按钮悬停效果 */  
        }   
        
        .product-image {  
            height: 50px;  
            width: 50px;  
            display: block;  
            margin: auto;  
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
                <h3 class="panel-title">商品列表</h3>  
            </div>  
            <div class="panel-body">  
                <div class="table-responsive scroll-container">  
                    <table class="product-table table table-bordered table-hover">  
                        <thead>  
                            <tr>  
                                <th>商品名称</th>  
                                <th>折扣价格</th>  
                                <th>图片</th>  
                                <th>选择</th>  
                            </tr>  
                        </thead>  
                        <tbody>  
                            <c:forEach items="${allProducts}" var="product">  
                                <tr class="product-row">  
                                    <td>${product.name}</td>  
                                    <td>${product.discount_price}</td>  
                                    <td>  
                                        <img src="static/images/${product.picture}" class="product-image">  
                                    </td>  
                                    <td><input type="checkbox" name="productSelect" value="${product.id}"></td>  
                                </tr>  
                            </c:forEach>  
                        </tbody>  
                    </table>  
                </div>  
                <div align="center">  
                    <a href="product/toAddProduct" class="btn btn-success">添加订单</a>  
                </div>  
            </div>  
        </div>  
    </div>
    <script>  
	    $(document).ready(function() {  
	        $(".btn-success").click(function(event) {  
	            event.preventDefault(); // 防止默认提交行为  
	
	            // 获取所有选中的商品名称  
	            let selectedProducts = [];  
	            $("input[name='productSelect']:checked").each(function() {  
	                let productName = $(this).closest("tr").find("td:first").text(); // 获取商品名称  
	                selectedProducts.push(productName);  
	            });  
	
	            // 检查是否有选中的商品  
	            if (selectedProducts.length === 0) {  
	                alert("请至少选择一个商品.");  
	                return;  
	            }  
	
	            // 发送 AJAX 请求到后端  
	            $.ajax({  
	                url: 'order/createOrder', // 后端接口  
	                type: 'POST',  
	                contentType: 'application/json',  
	                data: JSON.stringify({ products: selectedProducts }),  
	                success: function(response) {  
	                    alert("订单已成功创建，订单号：" + response.orderId);  
	                    window.location.href = 'order/toOrderMainPage'  
	                },  
	                error: function(xhr, status, error) {  
	                    alert("创建订单时出错: " + error);  
	                }  
	            });  
	        });  
	    });  
	</script>  
</body>  

</html>