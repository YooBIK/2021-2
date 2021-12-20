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
            	 //사용될 쿼리를 String자료형으로 저장
            	String sql= "SELECT S.rating, AVG(S.age) AS avgage FROM sailors S WHERE S.age>=18 GROUP BY S.rating HAVING 1<(SELECT COUNT(*) FROM sailors S2 WHERE S.rating=S2.rating AND S2.age>=18)";
                String update_sql = "UPDATE sailors SET age=30 WHERE sname=\"Andy\"";
                //execute query
            	try (ResultSet rs = stmt.executeQuery(sql)) {
                    //position result to first
            			System.out.println("Before Update"+ "\n"+"rating"+ "\t" + "avgage");
                	while(rs.next()) {						//ResultSet rs를 순회하면서 값을 출력하고, rating,avgage 쌍을 해쉬 맵에 저장
                		int rating = rs.getInt("rating");
                		float avgage = rs.getFloat("avgage");
                		System.out.println(rating + "\t" + avgage);
                		map.put(rating,avgage);
                	}
                	
            	}     
            	stmt.executeUpdate(update_sql);	//테이블을 업데이트하는 쿼리 수행
            	//execute query
                try(ResultSet rs2= stmt.executeQuery(sql)){   
                	System.out.println("After Update"+"\n" + "rating"+ "\t" + "avgage");
                	while(rs2.next()) {					//ResultSet rs2를 순회하면서 해쉬 맵에 저장되어 있는 rating,avgage 와 비교하며 rating은 같고, avgage가 다른 경우 rating을 출력  
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
    
