class ipaddr {
	int address;
	int netmask;
    int netaddr;
    int bcast;

	public ipaddr(int addr) {}
	public ipaddr(String cidr) {
        String [] parts = cidr.split("/");
        this.setMask(Integer.parseInt(parts[1]));
        this.setAddress(parts[0]);
    }

	void setMask(int nm) {
        for(int i = 0; i < nm; i++){
            this.netmask = this.netmask << 1;
            this.netmask = this.netmask + 1;
        }
        this.netmask = this.netmask << (32-nm);
        //this.printHex(this.netmask);
    }
    
    void setAddress(String ip){
        String [] octets = ip.split("\\.");
        //int a = Integer.parseInt(octets[0]);
        for(int i = 0; i < 4; i++){
            int o = Integer.parseInt(octets[i]);
            this.address = this.address << 8;
            this.address += o;
        }
    }
     
    public void netInfo(){
        this.netaddr = this.address & this.netmask;
        this.bcast = netaddr + (~this.netmask);
        int usable = bcast - netaddr - 1;
        System.out.println("Network address: " + this.toString(this.netaddr)+"\nBroadcast address: "+ this.toString(this.bcast)+
                           "\nNumber of usable addresses: "+usable);
    }
    
    public void listAdds(){
        //print usable addresses
        for(int i = this.netaddr+1; i < this.bcast; i++){
            System.out.println(this.toString(i));
        }
    }

	void printHex(int i) {
		System.out.println( String.format("0x%08X", i) );
	}

    //@Override
    public String toString(int ip) {
        //using ip
        //convert an int to a string
        String sip = "";
        for(int i = 3; i >= 0; i--){
            int octet = (ip >>> (i*8)) & 0xff;; //0x0000000a
            if(i > 0)
                sip += octet + ".";
            else
                sip += octet;
        }
        return sip;
    }
}