import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
import serial

class ServoController(Node):
    def __init__(self):
        super().__init__('servo_controller')
        self.subscription = self.create_subscription(
            Int32MultiArray,
            'ldr_data',
            self.listener_callback,
            10)
        self.ser = serial.Serial('/dev/ttyACM0', 9600)
        self.angle = 90

    def listener_callback(self, msg):
        left, right = msg.data
        threshold = 10  # Gürültü eşiği
        delta = left - right

        if abs(delta) > threshold:
            if delta > 0:
                self.angle -= 2
            else:
                self.angle += 2

            self.angle = max(0, min(180, self.angle))
            command = f"S:{self.angle}\n"
            self.ser.write(command.encode())

def main(args=None):
    rclpy.init(args=args)
    node = ServoController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
