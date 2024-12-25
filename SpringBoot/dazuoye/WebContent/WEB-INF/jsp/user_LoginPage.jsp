<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false" %>
    <%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
        <% String path=request.getContextPath(); String basePath=request.getScheme() + "://" + request.getServerName()
			+ ":" + request.getServerPort() + path + "/" ; %>
            <!DOCTYPE html>
            <html>

            <head>
                <base href="<%=basePath%>">
                <meta charset="UTF-8">
                <title>登录页面</title>
                <link href="static/css/bootstrap.min.css" rel="stylesheet">
                <style>
                    body {
                        background-color: #e9ecef;
                    }
                    
                    .container {
                        margin-top: 50px;
                    }
                    
                    .bg-primary {
                        padding: 15px;
                        border-radius: 5px;
                    }
                    
                    h2 {
                        color: #fff;
                    }
                    
                    .btn {
                        margin-right: 10px;
                    }
                    
                    .error-message {
                        color: red;
                        margin-top: 10px;
                    }
                </style>
            </head>

            <body class="bg-info">
                <div class="container">
                    <div class="bg-primary text-center">
                        <h2>商城管理系统</h2>
                    </div>
                    <br>
                    <form:form action="user/login" modelAttribute="user" method="post" cssClass="form-horizontal">
                        <div class="form-group has-success">
                            <label class="col-sm-2 col-md-2 control-label">用户名</label>
                            <div class="col-sm-4 col-md-4">
                                <form:input cssClass="form-control" placeholder="请输入您的用户名" path="uname" required="required" />
                            </div>
                        </div>
                        <div class="form-group has-success">
                            <label class="col-sm-2 col-md-2 control-label">密码</label>
                            <div class="col-sm-4 col-md-4">
                                <form:password cssClass="form-control" placeholder="请输入您的密码" path="upwd" required="required" />
                            </div>
                        </div>
                        <div class="form-group">
                            <div class="col-sm-offset-2 col-sm-10">
                                <button type="submit" class="btn btn-success">登录</button>
                                <button type="reset" class="btn btn-primary">重置</button>
                                <p class="help-block">没账号，请<a href="user/toRegister">注册</a>。</p>
                            </div>
                        </div>
                        <div class="error-message">
                            ${errorMessage}
                        </div>
                    </form:form>
                </div>
            </body>

            </html>