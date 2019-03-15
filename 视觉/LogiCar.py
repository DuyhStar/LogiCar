import sensor, image, time
from pyb import UART

# 如果要保证颜色追踪效果的话， 需要对环境的严格控制
# 晚上光源的冷暖色等，都会对颜色追踪造成很大的影响

# 颜色阈值的设定可以在 工具(Tools) -> 机器视觉(Machine Vision) -> 阈值编辑器(Threshold Editor) 中调试
red_threshold   = ( 24,  34,  36,  52,  13,  34) # 红色阈值
green_threshold = (  8,  23, -28,  -9,  -4,  22) # 绿色阈值
blue_threshold  = ( 16,  25,  -6,  23, -45, -17) # 蓝色阈值

# 颜色代码是find_blobs返回的blob对象中的一个成分， 用于标识，该色块是由在哪个阈值下选择的
red_color_code   = 1 # 红色的颜色代码
green_color_code = 2 # 绿色的颜色代码
blue_color_code  = 4 # 蓝色的颜色代码

sensor.reset()                      # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 选择像素模式 RGB565.
sensor.set_framesize(sensor.QVGA)   # use QQVGA for speed.
sensor.skip_frames(10)              # Let new settings take affect.
sensor.set_auto_whitebal(False)     #关闭白平衡。白平衡是默认开启的，在颜色识别中，需要关闭白平衡。

clock = time.clock() # Tracks FPS.

uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)

def qrcode_detect():
    while(True):
        img = sensor.snapshot()
        img.lens_corr(1.8)

        code = img.find_qrcodes()

        if code:
            uart.write(code.payload())
            break;

def color_detect():
    while(True):
        img = sensor.snapshot() # 拍照，返回图像

        # 颜色阈值约束(color_threshold,数组格式),像素阈值pixel_threshold,色块面积大小阈值(area_threshold)
        blobs = img.find_blobs([red_threshold, green_threshold, blue_threshold], area_threshold=150)

        #如果找到了目标颜色
        if blobs:
            for blob in blobs:#迭代找到的目标颜色区域
                x          = blob[0]
                y          = blob[1]
                width      = blob[2]
                height     = blob[3]
                center_x   = blob[5]
                center_y   = blob[6]
                color_code = blob[8]

                # 添加颜色说明
                if color_code == red_color_code:
                    img.draw_string(x, y - 10, "RED", color = (0xFF, 0xFF, 0xFF), scale = 2)
                elif color_code == green_color_code:
                    img.draw_string(x, y - 10, "GREEN", color = (0xFF, 0xFF, 0xFF), scale = 2)
                elif color_code == blue_color_code:
                    img.draw_string(x, y - 10, "BLUE", color = (0xFF, 0xFF, 0xFF), scale = 2)

                img.draw_rectangle([x, y, width, height]) #用矩形标记
                img.draw_cross(center_x, center_y)        #在中心画十字形标记



while(True):
    if uart.any():
        tmp_data = uart.readchar()

        if tmp_data == 49:    # 收到字符 1
            # 二维码识别
            # qrcode_detect()
            uart.write('qrcode')
            pass
        elif tmp_data == 50:    # 收到字符 2
            # 颜色识别
            # color_detect()
            uart.write('color')
            pass

        else:
            pass

    else:
        pass








