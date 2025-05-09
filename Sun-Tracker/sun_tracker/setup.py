from setuptools import setup

package_name = 'sun_tracker'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='F4LD3X',
    maintainer_email='mehmetyilmz16@gmail.com',
    description='Güneş takip sistemi için ROS 2 paketi',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'ldr_reader = sun_tracker.ldr_reader:main',
            'servo_controller = sun_tracker.servo_controller:main',
        ],
    },
)
