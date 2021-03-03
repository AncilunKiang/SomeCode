from selenium import webdriver
from selenium.webdriver import ActionChains
from PIL import Image
from aip import AipOcr
import yagmail
import time

# 以下为参数设置
APP_ID = '23531718 '  # 百度OCR APP_ID
API_KEY = 'GggxCG9qTqRpGkoaFckw1NYK'  # 百度OCR API_KEY
SECRET_KEY = 'YqW1MqpFmvKsk0plUFAQVOM2a2RO8pM3'  # 百度OCR SECRET_KEY
student_id = '311809000922'  # 统一认证号（学号）
student_password = '250619'  # 统一身份认证密码
email = '15037495893@163.com'  # 发件邮箱
email_password = 'AHUTQWYOJDICNPNE'  # 发件邮箱授权码
rec_email = '779246564@qq.com'  # 收件邮箱


print('正在打开Chrome\n')
option = webdriver.ChromeOptions()
option.add_argument('--headless')  # 设置为无头模式
option.add_argument("--window-size=1920,1080")  # 设置浏览器分辨率
browser = webdriver.Chrome(options=option)  # 启动Chrome
print('Chrome打开成功\n')

try:
    print('正在打开请求办理页面\n')
    browser.get("https://zhlg.hpu.edu.cn/hnlg_portal/guide?id=552A8690-D59D-4CEB-9C85-9789A9F3EA4D")  # 网上办事大厅/每日健康上报
    print('请求办理页面打开成功\n')

    print('定位"我要办理"\n')
    button = browser.find_element_by_css_selector("[type=button][value=我要办理]")  # 定位“我要办理”按钮
    ActionChains(browser).move_to_element(button).click(button).perform()  # 单击
    print('点击成功\n')

    print('定位验证码\n')
    windows = browser.window_handles  # 获取窗口句柄
    browser.switch_to.window(windows[-1])  # 转换到最新打开的窗口
    png = browser.find_element_by_css_selector("[alt=验证码]")  # 定位验证码
    png.screenshot('capture.png')  # 截图
    img = Image.open('capture.png')  # 验证码图片
    img = img.convert('L')  # 设为灰度模式
    img.save('capture2.png')  # 保存处理后的验证码图片
    print('验证码截取成功\n')

    print('正在识别验证码\n')
    client = AipOcr(APP_ID, API_KEY, SECRET_KEY)  # 初始化对象
    image = open('capture2.png', 'rb').read()  # 读取图片
    options = {'language_type': 'ENG', }  # 模式设置
    result = client.basicGeneral(image, options)  # 进行识别
    for word in result['words_result']:
        capture2 = word['words']  # 获取结果
    res = int(capture2[0]) + int(capture2[4])  # 验证码运算
    print('识别成功\n')

    print('正在填写登录信息\n')
    browser.find_element_by_css_selector("[type=text][name=username]").send_keys(student_id)  # 输入账号
    browser.find_element_by_css_selector("[type=password][name=password]").send_keys(student_password)  # 输入密码
    browser.find_element_by_css_selector("[type=text][id=captcha]").send_keys(res)  # 输入验证码
    print('填写完成\n')
    print('定位"登录"\n')
    element1 = browser.find_element_by_xpath("//*[@id='login-submit']")  # 定位登录按钮
    browser.execute_script("arguments[0].click();", element1)  # 点击（解决元素重叠）
    print('点击成功\n')
    print('等待页面加载\n')
    time.sleep(15)

    print('定位"提交"\n')
    windows = browser.window_handles  # 获取窗口句柄
    browser.switch_to.window(windows[-1])  # 转换到最新打开的窗口
    browser.find_element_by_link_text("提交").click()  # 点提交
    print('点击成功\n')
    time.sleep(3)
    print('定位"确认"\n')
    browser.find_element_by_xpath("//*[starts-with(@id,'dialog_container_')]/div[2]/button[1]").click()  # 点确认
    print('点击成功\n')
    time.sleep(5)

    print('调整画面大小及位置\n')
    browser.execute_script("document.body.style.zoom='0.75'")  # 缩小至75%（保证截到姓名和流水号）
    browser.execute_script("var q=document.documentElement.scrollTop=0")  # 滚动到顶部
    time.sleep(1)
    browser.save_screenshot('success.png')  # 截图
    print('截图成功\n')
except:
    print("执行异常\n")
    print('正在发送通知邮件\n')
    yag = yagmail.SMTP(user=email, password=email_password, host="smtp.163.com")  # 创建SMTP对象
    content = [
        time.strftime("%Y/%m/%d") + time.strftime(" %H:%M:%S") + '执行失败，请及时处理'
    ]
    yag.send(to=rec_email, subject="自动健康打卡执行失败", contents=content)  # 发送邮件
    yag.close()  # 关闭连接
    print('发送成功\n')
else:
    time.sleep(3)
    print('正在发送通知邮件\n')
    yag = yagmail.SMTP(user=email, password=email_password, host="smtp.163.com")  # 创建SMTP对象
    content = [
        time.strftime("%Y/%m/%d") + time.strftime(" %H:%M:%S") + '完成，凭证见附件'
    ]
    yag.send(to=rec_email, subject="今日健康打卡已完成", contents=content, attachments=["success.png"])  # 发送邮件
    yag.close()  # 关闭连接
    print('发送成功\n')
finally:
    print('程序将在3s后退出\n')
    time.sleep(3)
    browser.quit()  # 关闭浏览器
    print('浏览器已关闭\n')
