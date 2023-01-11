import java.util.Scanner;

public class IPadd{
    public static void main(String[] args) throws Exception{
        Scanner cin = new Scanner(System.in);
        int flag;
        
        while(true){
            flag = 1;
            System.out.println("Enter a cidr IP address: ");

            String ip = cin.nextLine();
            
            String [] p = ip.split("/");
            String [] check = p[0].split("\\.");
            for(int i = 0; i < 4; i++){
                if((Integer.parseInt(check[i]) > 255) || (Integer.parseInt(check[i]) < 0)){
                    System.out.println("Not a valid IP");
                    flag = 0;
                    break;
                }
            }
            
            if(Integer.parseInt(p[1]) > 32){
                flag = 0;
                System.out.println("Not a valid IP");
            }
            if(check.length != 4){
                flag = 0;
                System.out.println("Not a valid IP");
            }
            
            if(flag == 1){
                ipaddr i = new ipaddr(ip);

                System.out.println("IP address: " + ip);
                i.netInfo();

                System.out.println();

                System.out.println("Would you like to print the available addresses?(Y or N)");
                String ans = cin.nextLine();
                System.out.println();

                if(ans.equals("Y"))
                    i.listAdds();
            }
            System.out.println();
        }
    }
}