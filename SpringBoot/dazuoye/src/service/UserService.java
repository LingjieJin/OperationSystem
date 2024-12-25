package service;

import javax.servlet.http.HttpSession;

import org.springframework.ui.Model;

import model.User;

public interface UserService {
	public String checkUname(User user);

	public String register(User user);

	public String login(User user, Model model, HttpSession session);
	
	public String loginOut(Model model, HttpSession session);

	public String mainpage(User user, Model model, int currentPage, HttpSession session);
	
	public String updatePwd(User user);
}
