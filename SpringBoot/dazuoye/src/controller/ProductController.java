package controller;

import java.io.IOException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

import model.Product;
import service.ProductService;

@Controller
@RequestMapping("/product")
public class ProductController {
	@Autowired
	private ProductService productService;
	
	@RequestMapping("/toAddProduct")
	public String toAddProduct(@ModelAttribute Product product) {
		return "product_addPage";
	}
	
	@RequestMapping("/addProduct")
	public String addProduct(@ModelAttribute Product product, Model model, HttpServletRequest  request, String act, HttpSession session) throws IllegalStateException, IOException {
		return productService.addProduct(product, model, request, act, session);
	}

	@RequestMapping("/selectAllProductsByPage")
	public String selectAllCardsByPage(Model model, int currentPage,  HttpSession session) {
		return productService.selectAllProductsByPage(model, currentPage, session);
	}
	
	@RequestMapping("/toDetail")
	public String detail(Model model,  HttpSession session, int id, String act) {
		return productService.detail(model, session, id, act);
	}
}
