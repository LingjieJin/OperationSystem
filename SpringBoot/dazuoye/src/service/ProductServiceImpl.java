package service;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.ui.Model;
import org.springframework.web.multipart.MultipartFile;

import dao.ProductMapper;
import model.Product;
import po.ProductTable;
import util.MyUtil;

@Service
public class ProductServiceImpl implements ProductService {
	@Autowired
	private ProductMapper productMapper;


	@Override
	public String selectAllProductsByPage(Model model, int currentPage, HttpSession session) {
		List<Map<String, Object>> allproducts = productMapper.selectAllProducts();

		int totalCount = allproducts.size();

		int pageSize = 5;
		int totalPage = (int) Math.ceil(totalCount * 1.0 / pageSize);
		List<Map<String, Object>> productsByPage = productMapper.selectAllProductsByPage((currentPage - 1) * pageSize,
				pageSize);
		model.addAttribute("allProducts", productsByPage);
		model.addAttribute("totalPage", totalPage);
		model.addAttribute("currentPage", currentPage);

		return "product_MainPage";
	}


	@Override
	public String addProduct(Product product, Model model, HttpServletRequest request, String act, HttpSession session)
			throws IllegalStateException, IOException {
		MultipartFile myfile = product.getPicture_file();
		if (!myfile.isEmpty()) {
			String path = request.getServletContext().getRealPath("/static/images/");
			String fileName = myfile.getOriginalFilename();
			String fileNewName = MyUtil.getNewFileName(fileName);
			File filePath = new File(path + File.separator + fileNewName);
			if (!filePath.getParentFile().exists()) {
				filePath.getParentFile().mkdirs();
			}
			myfile.transferTo(filePath);
			product.setPicture(fileNewName);
		}

		if ("add".equals(act)) {
			int n = productMapper.addProduct(product);
			if (n > 0)
				return "redirect:/product/selectAllProductsByPage?currentPage=1";
			
			return "product_addPage";
		} else {
			int id = (int) session.getAttribute("product_id");
			product.setId(id);
			
			int n = productMapper.updateProduct(product);
			if (n > 0)
				return "redirect:/product/selectAllProductsByPage?currentPage=1";
			
			return "product_updatePage";
		}
	}

	/**
	 * 打开详情与修改页面
	 */
	@Override
	public String detail(Model model, HttpSession session, int id, String act) {
		ProductTable ct = productMapper.selectAProduct(id);
		model.addAttribute("product", ct);
		if ("detail".equals(act)) {
			return "product_DetailPage";
		} else if ("update".equals(act)) {
			session.setAttribute("product_id", ct.getId());
			return "product_updatePage";
		} else {
			//
			int n = productMapper.deleteAProduct(id);
			if (n > 0) {
				return "redirect:/product/selectAllProductsByPage?currentPage=1";
			}
			return "product_MainPage";
		}
	}

}
