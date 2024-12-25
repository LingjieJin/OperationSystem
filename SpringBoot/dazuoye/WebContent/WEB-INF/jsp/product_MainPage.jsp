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
                            <h3 class="panel-title">商品列表</h3>
                        </div>
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-bordered table-hover">
                                    <thead>
                                        <tr>
                                            <th>商品名称</th>
                                            <th>商品价格</th>
                                            <th>商品折扣价格</th>
                                            <th>商品库存</th>
                                            <th>商品图片</th>
                                            <th>操作</th>
                                        </tr>
                                    </thead>
                                    <tbody class="text-center">
                                        <c:if test="${totalPage != 0 }">
                                            <c:forEach items="${allProducts}" var="product">
                                                <tr>
                                                    <td>${product.name}</td>
                                                    <td>${product.price}</td>
                                                    <td>${product.discount_price}</td>
                                                    <td>${product.counts}</td>
                                                    <td>
                                                        <img src="static/images/${product.picture}" style="height: 50px; width: 50px; display: block; margin: auto;">
                                                    </td>
                                                    <td>
                                                        <a href="product/toDetail?id=${product.id}&act=detail" target="_blank" class="btn btn-info btn-sm">详情</a>
                                                        <a href="product/toDetail?id=${product.id}&act=update" target="_blank" class="btn btn-warning btn-sm">修改</a>
                                                        <a href="product/toDetail?id=${product.id}&act=delete" onclick="return confirm('确定要删除吗?');" class="btn btn-danger btn-sm">删除</a>
                                                    </td>
                                                </tr>
                                            </c:forEach>
                                            <tr>
                                                <td colspan="7" align="right">
                                                    <ul class="pagination">
                                                        <li class="disabled"><a>第<span>${currentPage}</span>页</a></li>
                                                        <li class="disabled"><a>共<span>${totalPage}</span>页</a></li>
                                                        <li>
                                                            <c:if test="${currentPage != 1}">
                                                                <a href="product/selectAllProductsByPage?currentPage=${currentPage - 1}">上一页</a>
                                                            </c:if>
                                                            <c:if test="${currentPage != totalPage}">
                                                                <a href="product/selectAllProductsByPage?currentPage=${currentPage + 1}">下一页</a>
                                                            </c:if>
                                                        </li>
                                                    </ul>
                                                </td>
                                            </tr>
                                        </c:if>
                                        <tr>
                                            <td colspan="7" align="center"><a href="product/toAddProduct" class="btn btn-success">添加商品</a></td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>

                    </div>
                </div>
            </body>

            </html>