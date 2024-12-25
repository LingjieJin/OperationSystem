package model;

import org.springframework.web.multipart.MultipartFile;

public class Product {
	private int id;
	private String name;
	private double price;
	private double discount_price;
	private int counts;
	private String picture;
	private MultipartFile picture_file;
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public double getPrice() {
		return price;
	}
	public void setPrice(double price) {
		this.price = price;
	}
	public double getDiscount_price() {
		return discount_price;
	}
	public void setDiscount_price(double discount_price) {
		this.discount_price = discount_price;
	}
	public int getCounts() {
		return counts;
	}
	public void setCounts(int counts) {
		this.counts = counts;
	}
	public String getPicture() {
		return picture;
	}
	public void setPicture(String picture) {
		this.picture = picture;
	}
	public MultipartFile getPicture_file() {
		return picture_file;
	}
	public void setPicture_file(MultipartFile picture_file) {
		this.picture_file = picture_file;
	}
	
	

}
