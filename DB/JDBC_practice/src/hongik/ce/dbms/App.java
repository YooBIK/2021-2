package hongik.ce.dbms;

import java.sql.*;
import java.util.HashMap;

public class App {
	public static void main( String[] args ) throws SQLException {
    	HashMap<Integer, Float> map = new HashMap<Integer, Float>();
        //create connection for a server installed in localhost, with a user "root" with no password
        try (Connection conn = DriverManager.getConnection("jdbc:mariadb://localhost/jdbc_connection_practice", "root",""
        		+ "")) {
            // create a Statement
            try (Statement stmt = conn.createStatement()) {
            	 //���� ������ String�ڷ������� ����
            	String sql= "SELECT S.rating, AVG(S.age) AS avgage FROM sailors S WHERE S.age>=18 GROUP BY S.rating HAVING 1<(SELECT COUNT(*) FROM sailors S2 WHERE S.rating=S2.rating AND S2.age>=18)";
                String update_sql = "UPDATE sailors SET age=30 WHERE sname=\"Andy\"";
                //execute query
            	try (ResultSet rs = stmt.executeQuery(sql)) {
                    //position result to first
            			System.out.println("Before Update"+ "\n"+"rating"+ "\t" + "avgage");
                	while(rs.next()) {						//ResultSet rs�� ��ȸ�ϸ鼭 ���� ����ϰ�, rating,avgage ���� �ؽ� �ʿ� ����
                		int rating = rs.getInt("rating");
                		float avgage = rs.getFloat("avgage");
                		System.out.println(rating + "\t" + avgage);
                		map.put(rating,avgage);
                	}
                	
            	}     
            	stmt.executeUpdate(update_sql);	//���̺��� ������Ʈ�ϴ� ���� ����
            	//execute query
                try(ResultSet rs2= stmt.executeQuery(sql)){   
                	System.out.println("After Update"+"\n" + "rating"+ "\t" + "avgage");
                	while(rs2.next()) {					//ResultSet rs2�� ��ȸ�ϸ鼭 �ؽ� �ʿ� ����Ǿ� �ִ� rating,avgage �� ���ϸ� rating�� ����, avgage�� �ٸ� ��� rating�� ���  
                		int rating = rs2.getInt("rating");
                		float avgage = rs2.getFloat("avgage");
                		System.out.println(rating + "\t" + avgage);
                		if(map.get(rating)!=avgage) {
                			System.out.println("Changed Group = " + rating);
                		}
                	}
                }
            }
        }
}
}
    
