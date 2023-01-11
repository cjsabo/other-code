public class sender{
    public static void main(String[] args) throws Exception{
        rdt r = new rdt("127.0.0.1", 9000, 5000);
        //System.out.println("Hello world");
        r.rdt_send("The Cubs are the greatest");
        r.rdt_send("What are you lookin at punk");
        //r.rdt_send("The force will be with you... always.");
    }
}

//packets are strings
//message|checksum|seq
//hello, world|jfalkjfdaklj==|0
//md5 checksum

//split("\\|"); java split takes a regex