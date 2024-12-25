<%@ page language="java" contentType="text/html; charset=UTF-8" isErrorPage="true" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%  
String path = request.getContextPath();
String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + path + "/";
%>
<!DOCTYPE html>
<html>
<head>
<base href="<%=basePath%>">
<meta charset="UTF-8">
<title>Insert title here</title>
<link href="static/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>  
	<c:if test="${mymessage == 'noLogin'}">
		<h2>没登录，您没有权限访问，请<a href="user/toLogin">登录</a>！</h2>
	</c:if>
	<c:if test="${mymessage == 'noError'}">
		<h2>服务器内部错误或资源不存在！</h2>
	</c:if>
</body>
</html>