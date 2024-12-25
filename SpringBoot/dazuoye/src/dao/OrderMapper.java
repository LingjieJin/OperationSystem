package dao;

import java.util.List;

import org.springframework.stereotype.Repository;

import model.Order;
import po.OrderTable;

@Repository
public interface OrderMapper {
	public List<OrderTable> getOrdersByUserID(int user_id);
	public int addOrder(Order order);
	public int deleteAOrder(int id);
}
