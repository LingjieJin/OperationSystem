package dao;

import java.util.List;

import org.springframework.stereotype.Repository;

import po.ProductOrder;

@Repository
public interface ProductOrderMapper {
	public List<ProductOrder> selectAllProductsByOrder(String order_id);
	public void addProductOrder(ProductOrder productOrder); 
	public void deleteAOrder(String order_id);
}
