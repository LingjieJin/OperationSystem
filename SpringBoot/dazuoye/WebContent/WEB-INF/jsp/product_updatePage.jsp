<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<!DOCTYPE html>
<html>
<head>
<base href="<%=basePath%>">
<meta charset="UTF-8">
<title>更新商品信息</title>
<link rel="stylesheet" href="static/css/bootstrap.min.css" />
</head>
<body>
	<br><br><br>
	<div class="container">
		<div class="bg-primary"  style="width:70%; height: 60px;padding-top: 0.5px;">
	       <h3 align="center">修改商品</h3>
	   </div><br>
		<form:form action="product/addProduct?act=update" method="post" class="form-horizontal" modelAttribute="product"  enctype="multipart/form-data" >
			<div class="form-group has-success">
				<label class="col-sm-2 col-md-2 control-label">商品编号</label>
				<div class="col-sm-4 col-md-4">
					<form:input  cssClass="form-control" placeholder="请输入商品编号" path="id"/>
				</div>
			</div>
			<div class="form-group has-success">
				<label class="col-sm-2 col-md-2 control-label">商品名称</label>
				<div class="col-sm-4 col-md-4">
					<form:input  cssClass="form-control" placeholder="请输入商品名称" path="name"/>
				</div>
			</div>
			<div class="form-group has-success">
				<label class="col-sm-2 col-md-2 control-label">商品价格</label>
				<div class="col-sm-4 col-md-4">
					<form:input  cssClass="form-control" placeholder="请输入商品价格" path="price"/>
				</div>
			</div>
			<div class="form-group has-success">
				<label class="col-sm-2 col-md-2 control-label">商品折扣价格</label>
				<div class="col-sm-4 col-md-4">
					<form:input  cssClass="form-control" placeholder="请输入商品折扣价格" path="discount_price"/>
				</div>
			</div>
			<div class="form-group has-success">
				<label class="col-sm-2 col-md-2 control-label">商品库存</label>
				<div class="col-sm-4 col-md-4">
					<form:input  cssClass="form-control" placeholder="请输入商品库存" path="counts"/>
				</div>
			</div>
			<div class="form-group has-success">
				  <label class="col-sm-2 col-md-2 control-label">商品图片</label>
				  <div class="col-sm-4 col-md-4">
		  				<input type="file" placeholder="请选择商品照片"  name="picture_file" class="form-control" />
				  </div>
			 </div>
			<div class="form-group">
				<div class="col-sm-offset-2 col-sm-10">
					<button type="submit"class="btn btn-success" >修改</button>
					<button type="reset" class="btn btn-primary" >重置</button>
				</div>
			</div>
		</form:form>
	</div>
</body>
</html>