//Cobi Sabo
//rdt 3.0 class for rdt sender
import java.io.*; 
import java.net.*;
import java.util.Arrays;
import java.util.Random;
import java.util.Base64;
import java.net.DatagramSocket;
import java.lang.Object.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.lang.String;

class rdt {

    DatagramSocket socket;
    String serverHostname;
    int serverPort;
    InetAddress IPAddress;
    int sequence;
    int timeout;
    Random rand;

    public rdt(String server, int port, int timeout) throws SocketException,UnknownHostException {
        serverHostname = new String (server);
        IPAddress = InetAddress.getByName(serverHostname); 
        serverPort = port;
        this.sequence = 0;
        this.timeout = timeout;
        rand = new Random();
        socket = new DatagramSocket();
        
    }

    public void rdt_send(String data) throws NoSuchAlgorithmException,UnknownHostException, IOException {
        try{
            byte[] packet = make_pkt(data,compute_checksum(data));
            udt_send(packet);
        }catch(NoSuchAlgorithmException e){
            System.out.println("Nope!");
        }
    }

    private byte[] make_pkt(String data, String cs) {
        String packet = data + "|" + cs +"|" + String.valueOf(this.sequence); //int in a string ?
        return packet.getBytes();
    }
    
    private void udt_send(byte[] packet) throws NoSuchAlgorithmException,UnknownHostException, IOException {    
        DatagramPacket sendPacket = new DatagramPacket(packet, packet.length, IPAddress, serverPort);
        
        socket.setSoTimeout(timeout);
        while(true){
            try{
                
                socket.send(sendPacket);
                //receive ACK
                byte[] receiveData = new byte[1024];
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                socket.receive(receivePacket);

                //check for ACK, checksum is valid, sequence is correct
                String data = new String(receivePacket.getData());
                String parts[] = data.split("\\|");
                if(!isCorrupt(data) && in_order(Integer.parseInt(parts[2].trim()))){
                    // great!!

                    this.sequence = (this.sequence+1)%2;
                    return;
                }

            } catch(SocketTimeoutException e){
                System.out.println("Socket timeout!");
            }catch(NoSuchAlgorithmException e){
                System.out.println("Not today!");
            }
        }
        //socket.close();
    }
    
    public String compute_checksum(String data) throws NoSuchAlgorithmException{
        try{
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(data.getBytes());
            byte[] digest = md.digest();
            String checksum = new String(Base64.getEncoder().encode(digest));
            return checksum;
        }catch(NoSuchAlgorithmException e){
            System.out.println("No algorithm!");
            return "0";
        }
    }

    public boolean verify_checksum(String message, String checksum) throws NoSuchAlgorithmException,IOException{
        try{
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(message.getBytes());
            byte[] digest = md.digest();
            String computed = new String(Base64.getEncoder().encode(digest));
            if(computed.equals(checksum)){return true;}
            return false;
        }catch(NoSuchAlgorithmException e){
            System.out.println("No algorithm!");
            return false;
        }
    }
    
    private boolean isAck(String packet){
        //get the sequence number from the ACK message
        String[] parts = packet.split("\\|"); 
        if (this.sequence == Integer.parseInt(parts[2])){
            return true;
        }
        return false;
    }
    
    private boolean in_order(int seq){
        if(this.sequence == seq){return true;}
        return false;
    }   
    
    private boolean isCorrupt(String packet) throws NoSuchAlgorithmException,IOException{
        try{
            String[] parts = packet.split("\\|");
            if(!verify_checksum(parts[0],parts[1]))
                return true;
            return false;
        }catch(NoSuchAlgorithmException e){
            System.out.println("Didn't work!");
        }
        return false;
    }
}