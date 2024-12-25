package service;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.ui.Model;

import dao.OrderMapper;
import dao.ProductMapper;
import dao.UserMapper;
import model.User;
import po.OrderTable;
import po.UserTable;

@Service
public class UserServiceImpl implements UserService {
	@Autowired
	private UserMapper userMapper;

	@Autowired
	private ProductMapper productMapper;

	@Autowired
	private OrderMapper orderMapper;


	@Override
	public String checkUname(User user) {
		List<UserTable> userList = userMapper.selectByUname(user);
		if (userList.size() > 0)
			return "no";
		return "ok";
	}

	/**
	 * 实现注册功能
	 */
	@Override
	public String register(User user) {
		if (userMapper.register(user) > 0)
			return "user_LoginPage";
		return "user_RegistPage";
	}

	/**
	 * 实现登录功能
	 */
	@Override
	public String login(User user, Model model, HttpSession session) {
		List<UserTable> list = userMapper.login(user);
		if (list.size() > 0) {
			UserTable usertable = list.get(0);
			session.setAttribute("userLogin", usertable);
			// 获取商品
			List<Map<String, Object>> allproducts = productMapper.selectAllProducts();
			int totalCount = allproducts.size();
			int currentPage = 1;
			// 计算共多少页
			int pageSize = 3;
			int totalPage = (int) Math.ceil(totalCount * 1.0 / pageSize);
			List<Map<String, Object>> productsByPage = productMapper
					.selectAllProductsByPage((currentPage - 1) * pageSize, pageSize);
			//
			model.addAttribute("page_products", productsByPage);
			model.addAttribute("totalPage", totalPage);
			model.addAttribute("currentPage", currentPage);

			// 获取订单
			List<OrderTable> allorder = orderMapper.getOrdersByUserID(usertable.getId());
			model.addAttribute("order_list", allorder);
			model.addAttribute("order_size", allorder.size());

			return "user_MainPage";
		} else {
			model.addAttribute("errorMessage", "用户名或密码错误！");
			return "user_LoginPage";
		}
	}
	
	/**
	 * 安全退出
	 */
	@Override
	public String loginOut(Model model, HttpSession session) {
		session.invalidate();
		model.addAttribute("user", new User());
		return "user_LoginPage";
	}
	
	/**
	 * 修改密码
	 */
	@Override
	public String updatePwd(User user) {
		user.setUpwd(user.getUpwd());
		userMapper.updatePwd(user);
		return "user_LoginPage";
	}
	

	@Override
	public String mainpage(User user, Model model, int currentPage, HttpSession session) {
		//
		UserTable myuser = (UserTable)session.getAttribute("userLogin");
		// 获取商品
		List<Map<String, Object>> allproducts = productMapper.selectAllProducts();
		int totalCount = allproducts.size();
		// 计算共多少页
		int pageSize = 3;
		int totalPage = (int) Math.ceil(totalCount * 1.0 / pageSize);
		List<Map<String, Object>> productsByPage = productMapper.selectAllProductsByPage((currentPage - 1) * pageSize,
				pageSize);
		//
		model.addAttribute("page_products", productsByPage);
		model.addAttribute("totalPage", totalPage);
		model.addAttribute("currentPage", currentPage);

		// 获取订单
		List<OrderTable> allorder = orderMapper.getOrdersByUserID(myuser.getId());
		model.addAttribute("order_list", allorder);
		model.addAttribute("order_size", allorder.size());

		return "user_MainPage";
	}
}
