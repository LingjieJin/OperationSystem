package controller;

import java.util.List;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

import service.OrderService;
import model.OrderResponse;
import model.OrderRequest;

@Controller
@RequestMapping("/order")
public class OrderController {
	
	@Autowired
	private OrderService orderService;
	
	@RequestMapping("/toOrderMainPage")
	public String toOrderMainPage(Model model,  HttpSession session) {
		return orderService.selectAllOrders(model, session);
	}
	
	@RequestMapping("/toOrderAddPage")
	public String toOrderAddPage(Model model,  HttpSession session) {
		return orderService.selectAllProducts(model, session);
	}
	
	@RequestMapping("/deleteOrder")
	public String deleteOrder(Model model,  HttpSession session, int id, String order_id) {
		return orderService.deleteOrder(model, session, id, order_id);
	}
	
	@PostMapping("/createOrder")  
    public ResponseEntity<?> createOrder(@RequestBody OrderRequest orderRequest, Model model,  HttpSession session) {  
		 try {  
		        List<String> selectedProducts = orderRequest.getProducts();  
		        String orderId = orderService.createOrder(model,session, selectedProducts);  
		        return ResponseEntity.ok(new OrderResponse(orderId));  
		    } catch (Exception e) {  
		        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR)  
		            .body("创建订单时出错: " + e.getMessage());  
		    } 
    }  
	
	@RequestMapping("/showDetail")
	public String detail(Model model,  HttpSession session, String order_id) {
		return orderService.showDetail(model, session, order_id);
	}
}
