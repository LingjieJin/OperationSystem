<!DOCTYPE html>  
<html lang="zh">  

<head>  
    <meta charset="UTF-8">  
    <title>商品添加到订单</title>  
    <link rel="stylesheet" href="static/css/bootstrap.min.css" />  
    <script src="js/jquery.min.js"></script>  
    <style>  
        body {  
            background-color: #f7f7f7;  
        }  

        .container {  
            display: flex;  
            justify-content: space-between;  
        }  

        .product-list,  
        .order-list {  
            width: 48%;  
            margin-top: 20px;  
        }  

        .product,  
        .order-item {  
            border: 1px solid #ddd;  
            padding: 15px;  
            margin-bottom: 10px;  
            background-color: #ffffff;  
            border-radius: 4px;  
        }  

        .btn-remove {  
            margin-top: 10px;  
        }  

        .order-item {  
            display: flex;  
            justify-content: space-between;  
            align-items: center;  
        }  
    </style>  
</head>  

<body>  
    <div class="container">  
        <!-- 左侧商品展示 -->  
        <div class="product-list">  
            <h3>商品展示</h3>  
            <div id="products">  
                <div class="product">  
                    <h5>商品名称 1</h5>  
                    <p>价格: ￥100</p>  
                    <button class="btn btn-primary btn-add" data-name="商品名称 1" data-price="100">加入订单</button>  
                </div>  
                <div class="product">  
                    <h5>商品名称 2</h5>  
                    <p>价格: ￥200</p>  
                    <button class="btn btn-primary btn-add" data-name="商品名称 2" data-price="200">加入订单</button>  
                </div>  
                <div class="product">  
                    <h5>商品名称 3</h5>  
                    <p>价格: ￥150</p>  
                    <button class="btn btn-primary btn-add" data-name="商品名称 3" data-price="150">加入订单</button>  
                </div>  
                <!-- 可以继续添加商品 -->  
            </div>  
        </div>  

        <!-- 右侧订单列表 -->  
        <div class="order-list">  
            <h3>订单内容</h3>  
            <div id="orderItems">  
                <!-- 订单项将通过 JavaScript 动态添加 -->  
                <p>暂无商品，添加商品后将显示在此处。</p>  
            </div>  
            <button id="btnSubmitOrder" class="btn btn-success" disabled>提交订单</button>  
        </div>  
    </div>  

    <script>  
        $(document).ready(function () {  
            let orderItems = [];  

            // 点击"加入订单"按钮  
            $('.btn-add').click(function () {  
                const productName = $(this).data('name');  
                const productPrice = $(this).data('price');  

                // 检查商品是否已加入订单  
                const existingItem = orderItems.find(item => item.name === productName);  
                if (!existingItem) {  
                    orderItems.push({ name: productName, price: productPrice });  
                    renderOrderItems();  
                } else {  
                    alert("该商品已在订单中。");  
                }  
            });  

            // 渲染订单项  
            function renderOrderItems() {  
                $('#orderItems').empty();  
                if (orderItems.length === 0) {  
                    $('#orderItems').append('<p>暂无商品，添加商品后将显示在此处。</p>');  
                } else {  
                    orderItems.forEach((item, index) => {  
                        $('#orderItems').append(`  
                            <div class="order-item">  
                                <span>${item.name} - ￥${item.price}</span>  
                                <button class="btn btn-danger btn-remove" data-index="${index}">删除</button>  
                            </div>  
                        `);  
                    });  
                    $('#btnSubmitOrder').removeAttr('disabled'); // 启用提交按钮  
                }  
            }  

            // 点击删除按钮  
            $('#orderItems').on('click', '.btn-remove', function () {  
                const index = $(this).data('index');  
                orderItems.splice(index, 1); // 从数组中删除该商品  
                renderOrderItems();  
            });  

            // 提交订单  
            $('#btnSubmitOrder').click(function () {  
                if (orderItems.length === 0) {  
                    alert('您的订单为空，无法提交。');  
                    return;  
                }  

                // 这里通常会有 AJAX 请求将订单发送到服务器  
                alert('订单提交成功！'); // 模拟提交  
                orderItems = []; // 清空订单  
                renderOrderItems(); // 更新订单视图  
            });  
        });  
    </script>  
</body>  

</html>