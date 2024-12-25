package model;

public class Admin {
	private int id;
	private String uname;
	private String upwd;
	private String reupwd;
	
	public String getUname() {
		return uname;
	}
	public void setUname(String uname) {
		this.uname = uname;
	}
	public String getUpwd() {
		return upwd;
	}
	public void setUpwd(String upwd) {
		this.upwd = upwd;
	}
	public String getReupwd() {
		return reupwd;
	}
	public void setReupwd(String reupwd) {
		this.reupwd = reupwd;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
}
