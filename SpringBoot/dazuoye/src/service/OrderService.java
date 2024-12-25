package service;

import java.util.List;

import javax.servlet.http.HttpSession;

import org.springframework.ui.Model;

public interface OrderService {
	public String selectAllOrders(Model model, HttpSession session);
	public String selectAllProducts(Model model, HttpSession session);
	public String createOrder(Model model, HttpSession session, List<String> products);
	public String deleteOrder(Model model, HttpSession session, int id, String order_id);
	public String showDetail(Model model, HttpSession session, String order_id);
	
}
