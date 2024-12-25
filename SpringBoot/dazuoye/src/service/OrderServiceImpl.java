package service;

import java.util.List;
import java.util.Map;
import java.util.UUID;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.ui.Model;

import dao.OrderMapper;
import dao.ProductMapper;
import dao.ProductOrderMapper;
import model.Order;
import po.OrderTable;
import po.ProductOrder;
import po.UserTable;

@Service
public class OrderServiceImpl implements OrderService {
	@Autowired
	private OrderMapper orderMapper;
	
	@Autowired
	private ProductMapper productMapper;
	
	@Autowired
	private ProductOrderMapper productOrderMapper;

	@Override
	public String selectAllOrders(Model model, HttpSession session) {
		UserTable user = (UserTable)session.getAttribute("userLogin");
		List<OrderTable> allorder = orderMapper.getOrdersByUserID(user.getId());

		model.addAttribute("order_list", allorder);
		model.addAttribute("order_size", allorder.size());

		return "order_MainPage";
	}
	
	@Override
	public String selectAllProducts(Model model, HttpSession session)
	{
		List<Map<String, Object>> allproducts = productMapper.selectAllProducts();
		model.addAttribute("allProducts", allproducts);

		return "order_add";
	}
	
	public String createOrder(Model model, HttpSession session, List<String> products) {   
        String orderId = generateRandomOrderId();  
        
        UserTable user = (UserTable)session.getAttribute("userLogin");
        Order new_order = new Order();
        new_order.setOrder_id(orderId);
        new_order.setUser_id(user.getId());
        orderMapper.addOrder(new_order);
        
        
        for (String product : products) {  
            ProductOrder productOrder = new ProductOrder();  
            productOrder.setOrder_id(orderId);  
            productOrder.setProduct_name(product);  
            productOrderMapper.addProductOrder(productOrder); 
        } 
        
        return orderId; 
    }
	
	public String deleteOrder(Model model, HttpSession session, int id, String order_id)
	{
		orderMapper.deleteAOrder(id);
		
		productOrderMapper.deleteAOrder(order_id);
		
		return "redirect:/order/toOrderMainPage";
	}
	
	public String showDetail(Model model, HttpSession session, String order_id)
	{
		List<ProductOrder> results = productOrderMapper.selectAllProductsByOrder(order_id);
		
		model.addAttribute("product_order_list", results);
		
		return "order_DetailPage";
	}
	
	private String generateRandomOrderId() {  
        return UUID.randomUUID().toString();  
    }
}
