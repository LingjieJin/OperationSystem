<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" isELIgnored="false"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<!DOCTYPE html>
<html>
<head>
<base href="<%=basePath%>">
<meta charset="UTF-8">
<title>商城管理系统</title>
<link href="static/css/bootstrap.min.css" rel="stylesheet">
<script src="static/js/jquery.min.js"></script>
<script src="static/js/bootstrap.min.js"></script>
</head>
<body>
	<div class="container-fruid">
		<div class="navbar navbar-default navbar-fixed-top" role="navigation"
			style="padding-left: 30px;">
			<ul class="nav navbar-nav">
				<li><a href="user/toMainPage">主页</a></li>
				<li><a href="product/selectAllProductsByPage?currentPage=1&act=select">商品管理</a></li>
				<li><a href="order/toOrderMainPage">订单管理</a></li>
				<li><a href="user/toUpdatePwdPage">修改密码</a></li>
				<li><a href="user/loginOut">安全退出</a></li>
			</ul>
		</div>
	</div>
</body>
</html>