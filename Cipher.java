public class Cipher {
    protected char[] encoder = new char[26]; 
    protected char[] decoder = new char[26]; 
    
    public Cipher(int rotation){
        for(int i = 0; i < 26; i++){
            encoder[i] = (char) ('A' + (i + rotation) % 26); 
            decoder[i] = (char) ('A' + (i - rotation + 26) % 26);
        }
    }

    public String encrypt(String message){
        return transform(message, encoder);
    }

    public String decrypt(String message){
        return transform(message, decoder); 
    }

    public String transform(String original, char[] code){
        char[] msg = original.toCharArray(); 
        for(int i = 0; i < msg.length; i++){
            int j = msg[i] - 'A';
            msg[i] = code[j]; 
        }
        return new String(msg); 
    }

    public static void main(String[] args){
        Cipher cipher = new Cipher(3); 
        System.out.println("Encryption code = " + new String(cipher.encoder)); 
        System.out.println("Decryption code = " + new String(cipher.decoder)); 
        String message = "DEEZ NUT'S"; 
        String coded = cipher.encrypt(message); 
        System.out.println("Secret: " + coded); 
        String answer = cipher.decrypt(message); 
        System.out.println("Message" + answer); 
    }
    
}; 
