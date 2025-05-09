import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
import serial

class LDRReader(Node):
    def __init__(self):
        super().__init__('ldr_reader')
        self.publisher_ = self.create_publisher(Int32MultiArray, 'ldr_data', 10)
        self.ser = serial.Serial('/dev/ttyACM0', 9600)
        self.timer = self.create_timer(0.2, self.timer_callback)

    def timer_callback(self):
        try:
            line = self.ser.readline().decode().strip()
            if ',' in line:
                parts = line.split(',')
                if len(parts) == 2:
                    values = list(map(int, parts))
                    msg = Int32MultiArray()
                    msg.data = values
                    self.publisher_.publish(msg)
        except Exception as e:
            self.get_logger().warn(f"Seri port okuma hatası: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = LDRReader()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
