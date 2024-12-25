package dao;

import java.util.List;

import org.springframework.stereotype.Repository;

import model.User;
import po.UserTable;

@Repository
public interface UserMapper {
	public List<UserTable> selectByUname(User myUser);
	public int register(User myUser);
	public List<UserTable> login(User myUser);
	public int updatePwd(User myUser);
}
