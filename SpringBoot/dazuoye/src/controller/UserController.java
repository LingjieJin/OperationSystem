package controller;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import model.User;
import po.UserTable;
import service.UserService;

@Controller
@RequestMapping("/user")
public class UserController {
	@Autowired
	private UserService userService;

	@RequestMapping("/toLogin")
	public String toLogin(@ModelAttribute User user) {
		return "user_LoginPage";
	}
	
	@RequestMapping("/login")
	public String login(@ModelAttribute User user, Model model, HttpSession session) {
		return userService.login(user, model, session);
	}

	@RequestMapping("/toRegister")
	public String toRegister(@ModelAttribute User user) {
		return "user_RegistPage";
	}
	
	@RequestMapping("/register")
	public String register(@ModelAttribute User user, Model model) {
		return userService.register(user);
	}
	
	
	@RequestMapping("/loginOut")
	public String loginOut(Model model, HttpSession session) {
		return userService.loginOut(model, session);
	}

	@RequestMapping("/toMainPage")
	public String toMainpage(@ModelAttribute User user) {
		return "redirect:/user/mainpage?currentPage=1";
	}
	
	@RequestMapping("/mainpage")
	public String mainpage(@ModelAttribute User user, Model model, int currentPage, HttpSession session) {
		return userService.mainpage(user, model, currentPage, session);
	}
	
	@RequestMapping("/toUpdatePwdPage")
	public String toUpdatePwd(@ModelAttribute User user,Model model, HttpSession session) {
		UserTable myuser = (UserTable)session.getAttribute("userLogin");
		model.addAttribute("update_user", myuser);
		return "user_UpdatePwdPage";
	}
	
	@RequestMapping("/updatePwd")
	public String updatePwd(@ModelAttribute User user,Model model, HttpSession session) {
		return userService.updatePwd(user);
	}

	@RequestMapping("/checkUname")
	@ResponseBody
	public String checkUname(@RequestBody User user) {
		return userService.checkUname(user);
	}

}
