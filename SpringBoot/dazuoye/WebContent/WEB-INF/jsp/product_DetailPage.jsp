<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<!DOCTYPE html>
<html>
<head>
<base href="<%=basePath%>">
<meta charset="UTF-8">
<title>商品详情</title>
<link rel="stylesheet" href="static/css/bootstrap.min.css" />
</head>
<body>

	<br><br><br>
	<div class="container">
		<div class="panel panel-primary">
			<div class="panel-heading">
				<h3 class="panel-title">商品详情</h3>
			</div>
			<div class="panel-body">
				<div class="table table-responsive">
					<table class="table table-bordered table-hover">
						<tbody class="text-center">
							<tr>
								<th>商品名称</th>
								<td>${product.name}</td>
							</tr>
							<tr>
								<th>商品价格</th>
								<td>${product.price}</td>
							</tr>
							<tr>
								<th>商品折扣价格</th>
								<td>${product.discount_price}</td>
							</tr>
							<tr>
								<th>商品库存</th>
								<td>${product.counts}</td>
							</tr>																																										
							<tr>
								<th>商品图片</th>
								<td>
									<img src="static/images/${product.picture}"
									style="height: 50px; width: 50px; display: block;">
								</td>
							</tr>
						</tbody>
					</table>
				</div>
			</div>
		</div>
	</div>
</body>
</html>