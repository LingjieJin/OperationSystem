package service;
import java.io.IOException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.springframework.ui.Model;

import model.Product;

public interface ProductService {
	public String selectAllProductsByPage(Model model, int currentPage,  HttpSession session);
	public String addProduct(Product product, Model model, HttpServletRequest  request, String act, HttpSession session) throws IllegalStateException, IOException;
	public String detail(Model model,HttpSession session, int id, String act);
}
