package dao;

import java.util.List;
import java.util.Map;

import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import model.Product;
import po.ProductTable;


@Repository
public interface ProductMapper {
	public List<Map<String, Object>> selectAllProducts();
	public List<Map<String, Object>> selectAllProductsByPage(@Param("startIndex") int startIndex, @Param("perPageSize") int perPageSize);
	public int addProduct(Product product);
	public int updateProduct(Product product);
	public ProductTable selectAProduct(int id);
	public int deleteAProduct(int id);
}
