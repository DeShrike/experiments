import socket
import struct
import textwrap

#https://www.youtube.com/watch?v=oKUkbMz5q7Y

TAB_1 = "\t - "
TAB_2 = "\t\t - "
TAB_3 = "\t\t\t - "
TAB_4 = "\t\t\t\t - "
TAB_5 = "\t\t\t\t\t - "

DATA_TAB_1 = "\t "
DATA_TAB_2 = "\t\t "
DATA_TAB_3 = "\t\t\t "
DATA_TAB_4 = "\t\t\t\t "
DATA_TAB_5 = "\t\t\t\t\t "

def get_mac_addr(bytes_addr):
    bytes_str = map("{:02x}".format, bytes_addr)
    return ":".join(bytes_str).upper()

def ethernet_frame(data):
    dest_mac, src_mac, proto = struct.unpack("! 6s 6s H", data[:14])
    return get_mac_addr(dest_mac), get_mac_addr(src_mac), socket.htons(proto), data[14:]

def ipv4(addr):
    return ".".join(map(str, addr))

def ipv4_packet(data):
    version_header_length = data[0]
    version = version_header_length >> 4
    header_length = (version_header_length & 15) * 4
    ttl, proto, src, target = struct.unpack("! 8x B B 2x 4s 4s", data[:20])
    return version, header_length, ttl, proto, ipv4(src), ipv4(target), data[header_length:]

def icmp_packet(data):
    icmp_type, code, checksum = struct.unpack("! B B H", data[:4])
    return icmp_type, code, checksum, data[4:]

def tcp_packet(data):
    src_port, dest_port, sequence, acknowledgement, offset_reserved_flags = struct.unpack("! H H L L H", data[:14])
    offset = (offset_reserved_flags >> 12) * 4
    flag_urg = (offset_reserved_flags & 32) >> 5
    flag_ack = (offset_reserved_flags & 16) >> 5
    flag_psh = (offset_reserved_flags & 8) >> 5
    flag_rst = (offset_reserved_flags & 4) >> 5
    flag_syn = (offset_reserved_flags & 2) >> 5
    flag_fin = offset_reserved_flags & 1
    return src_port, dest_port, sequence, acknowledgement, flag_urg, flag_ack, flag_psh, flag_rst, flag_syn, flag_fin, data[offset:]

def udp_segment(data):
    src_port, dest_port, size = struct.unpack("! H H 2x H", data[:8])
    return src_port, dest_port, size, data[8:]

def format_multi_line(prefix, string, size = 80):
    size -= len(prefix)
    if isinstance(string, bytes):
        string = "".join(r"\x{:02x}".format(byte) for byte in string)
        if size % 2:
            size -= 1
    return "\n".join([prefix + line for line in textwrap.wrap(string, size)])

def main():
    conn = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(3))
    pcount = 0
    
    while True:
        if pcount >= 100:
            break
        raw_data, addr = conn.recvfrom(65536)
        dest_mac, src_mac, eth_proto, data = ethernet_frame(raw_data)
        print("\nEthernet Frame:")
        print(TAB_1 + f"Destination: {dest_mac}, Source: {src_mac}, Protocol: {eth_proto}")

        # 8 for IPv4
        if eth_proto == 8:
            pcount += 1
            version, header_length, ttl, proto, src, target, data = ipv4_packet(data)
            print(TAB_1 + "IPv4 Packet:")
            print(TAB_2 + f"Version: {version}, Header Length: {header_length}, TTL: {ttl}")
            print(TAB_2 + f"Protocol: {proto}, Source: {src}, Destination: {target}")

            if proto == 1:
                icmp_type, code, checksum, data = icmp_packet(data)
                print(TAB_3 + "ICMP Packet:")
                print(TAB_4 + f"Type: {icmp_type}, Code: {code}, Checksum: {checksum}")
                print(format_multi_line(DATA_TAB_4, data))
            elif proto == 6:
                src_port, dest_port, sequence, acknowledgement, flag_urg, flag_ack, flag_psh, flag_rst, flag_syn, flag_fin, data = tcp_packet(data)
                print(TAB_3 + "TCP Packet:")
                print(TAB_4 + f"Source Port: {src_port}, Destination Port: {dest_port}")
                print(TAB_4 + f"Sequence: {sequence}, Acknowledgement: {acknowledgement}")
                print(TAB_4 + "Flags:")
                print(TAB_5 + f"URG: {flag_urg}, ACK: {flag_ack}, PSH: {flag_psh}; RST: {flag_rst}, SYN: {flag_syn}, FIN: {flag_fin}")
                print(format_multi_line(DATA_TAB_5, data))
            elif proto == 17:
                src_port, dest_port, size, data = udp_segment(data)
                print(TAB_3 + "UDP Packet:")
                print(TAB_4 + f"Source Port: {src_port}, Destination Port: {dest_port}, Size: {size}")
                print(format_multi_line(DATA_TAB_4, data))



if __name__ == "__main__":
    main()
