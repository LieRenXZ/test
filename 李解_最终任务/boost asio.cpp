#include <iostream> 
#include <boost/asio.hpp> 
#include <boost/bind.hpp> 

using  namespace std ; 
using  namespace boost :: asio ; 

int main ( int argc,  char * argv [ ] ) 
{ 
        io_service iosev ; 
         // 串口COM1, Linux下为“/dev/ttyS0” 
        serial_port sp (iosev,  "COM1" ) ; 
         // 设置参数 
        sp. set_option (serial_port :: baud_rate (19200 ) ) ; 
        sp. set_option (serial_port :: flow_control (serial_port :: flow_control :: none ) ) ; 
        sp. set_option (serial_port :: parity (serial_port :: parity :: none ) ) ; 
        sp. set_option (serial_port :: stop_bits (serial_port :: stop_bits :: one ) ) ; 
        sp. set_option (serial_port :: character_size (8 ) ) ; 
         // 向串口写数据 
        write (sp, buffer ( "Hello world", 12 ) ) ; 

         // 向串口读数据 
        boost :: asio :: streambuf buf ; 
        // 一直读到遇到空格为止 
        read_until (sp, buf,  ' ' ) ; 
        copy (istream_iterator < char > (istream ( &buf ) >>noskipws ), 
        istream_iterator < char > ( ), 
        ostream_iterator < char > ( cout ) ) ;; 

        iosev. run ( ) ; 
         return  0 ; 
}