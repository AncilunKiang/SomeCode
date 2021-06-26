from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from PIL import Image
from aip import AipOcr
import yagmail
import time
import threading
import sets


def develop_strategy():  # 时间规划
    w = int(time.strftime("%w")) + 1
    s1 = sets.planning[w][1:]
    return s1


def get_seat_num():  # 获取座位号
    return sets.planning[int(time.strftime("%w")) + 1][0]


def timing(t):  # 定时执行
    while time.strftime("%H:%M") != t:
        time.sleep(0.1)
    time.sleep(0.1)


def reliable_find(browser, wt, xpath):  # 可靠的定位
    element = WebDriverWait(browser, wt).until(
        EC.presence_of_element_located((By.XPATH, xpath)))
    return element


def open_chrome(url):  # 打开浏览器
    print('正在打开Chrome\n')
    option = webdriver.ChromeOptions()
    option.add_argument('--headless')  # 设置为无头模式
    option.add_argument("--window-size=1920,1080")  # 设置浏览器分辨率
    browser = webdriver.Chrome(options=option)  # 启动Chrome
    print('Chrome打开成功\n')
    print('正在打开图书馆空间预约系统\n')
    browser.get(url)
    print('图书馆空间预约系统打开成功\n')
    return browser


def sign_in(browser, s_id, password):  # 登录
    print('从统一平台登录\n')
    button = browser.find_element_by_css_selector("[type=button][value=从统一平台登录]")  # 定位“从统一平台登录”按钮
    ActionChains(browser).move_to_element(button).click(button).perform()  # 单击
    print('点击成功\n')
    time.sleep(1)
    print('定位验证码\n')
    windows = browser.window_handles  # 获取窗口句柄
    browser.switch_to.window(windows[-1])  # 转换到最新打开的窗口
    png = browser.find_element_by_css_selector("[alt=验证码]")  # 定位验证码
    png.screenshot(sets.file_path + 'capture.png')  # 截图
    img = Image.open(sets.file_path + 'capture.png')  # 验证码图片
    img = img.convert('L')  # 设为灰度模式
    img.save(sets.file_path + 'capture2.png')  # 保存处理后的验证码图片
    print('验证码截取成功\n')
    print('正在识别验证码\n')
    # client = AipOcr(APP_ID, API_KEY, SECRET_KEY)  # 初始化对象
    client = AipOcr(sets.APP_ID, sets.API_KEY, sets.SECRET_KEY)  # 初始化对象
    image = open(sets.file_path + 'capture2.png', 'rb').read()  # 读取图片
    options = {'language_type': 'ENG', }  # 模式设置
    result = client.basicGeneral(image, options)  # 进行识别
    for word in result['words_result']:
        capture2 = word['words']  # 获取结果
    res = int(capture2[0]) + int(capture2[4])  # 验证码运算
    print('识别成功\n')
    print('正在填写登录信息\n')
    browser.find_element_by_css_selector("[type=text][name=username]").send_keys(s_id)  # 输入账号
    browser.find_element_by_css_selector("[type=password][name=password]").send_keys(password)  # 输入密码
    browser.find_element_by_css_selector("[type=text][id=captcha]").send_keys(res)  # 输入验证码
    print('填写完成\n')
    print('定位"登录"\n')
    element1 = browser.find_element_by_xpath("//*[@id='login-submit']")  # 定位登录按钮
    browser.execute_script("arguments[0].click();", element1)  # 点击（解决元素重叠）
    print('点击成功\n')


def layout_and_seat_selection(browser, seat, begin, end, tt_max):  # 布局选座
    if int(time.strftime("%H")) < 19:
        d = '//*[@id="options_onDate"]/a'
    else:
        d = '//*[@id="options_onDate"]/a[2]'
    st = "//*[starts-with(@id,'seat_')]/a[contains(text(), '" + seat + "')]"
    b_time = '//*[@id="startTime"]/dl/ul/li[*]/a[contains(text(), "' + begin + '")]'
    e_time = '//*[@id="endTimeCotent"]/li[*]/a[contains(text(), "' + end + '")]'
    step = 0
    while tt_max > 0:
        tt_max -= 1
        if step == 0:
            try:
                button0 = reliable_find(browser, 3, '/html/body/div[4]/div[1]/ul/li[2]/a')
                ActionChains(browser).move_to_element(button0).click().perform()
            except BaseException:
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('正在选择日期\n')
        if step == 1:
            try:
                button1 = browser.find_element_by_xpath('//*[@id="display_onDate"]')  # 选择日期下拉按钮
                ActionChains(browser).move_to_element(button1).click().perform()
                time.sleep(0.2)
                date = browser.find_element_by_xpath(d)  # 选择日期
                ActionChains(browser).move_to_element(date).move_by_offset(1, 1).click().perform()  # 偏移点击
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('正在选择场馆\n')
        if step == 2:
            try:
                button2 = browser.find_element_by_xpath('//*[@id="display_building"]')  # 选择场馆下拉按钮
                ActionChains(browser).move_to_element(button2).click().perform()
                time.sleep(0.2)
                building = browser.find_element_by_xpath(
                   '//*[@id="options_building"]/a[contains(text(), "南校区第二图书馆")]')  # 选择场馆
                ActionChains(browser).move_to_element(building).move_by_offset(0.5, 0.5).click().perform()  # 偏移点击
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('正在选择楼层\n')
        if step == 3:
            try:
                button3 = browser.find_element_by_xpath('//*[@id="display_floor"]')  # 选择楼层下拉按钮
                ActionChains(browser).move_to_element(button3).click().perform()
                time.sleep(0.2)
                floor = browser.find_element_by_xpath(
                    '//*[@id="options_floor"]/a[contains(text(), "南校区第二图书馆7层")]')  # 选择楼层
                ActionChains(browser).move_to_element(floor).move_by_offset(0.5, 0.5).click().perform()  # 偏移点击
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('点击查询\n')
        print('选择IV\n')
        if step == 4:
            try:
                button4 = browser.find_element_by_xpath('//*[@id="findRoom"]')  # 点击查询
                ActionChains(browser).move_to_element(button4).click().perform()
                button5 = reliable_find(browser, 2, '//*[@id="room_31"]')  # 选择IV
                ActionChains(browser).move_to_element(button5).click().perform()
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('点击座位\n')
        if step == 5:
            try:
                button6 = reliable_find(browser, 3, st)  # 座位号
                ActionChains(browser).move_to_element(button6).click().perform()
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
        print('选择开始时间\n')
        if step == 6:
            try:
                button7 = reliable_find(browser, 2, b_time)  # 开始时间
                ActionChains(browser).move_to_element(button7).click().perform()
            except BaseException:
                step -= 1
                continue
            else:
                time.sleep(0.1)
                step += 1
        print('选择结束时间\n')
        if step == 7:
            try:
                button8 = reliable_find(browser, 2, e_time)  # 结束时间
                ActionChains(browser).move_to_element(button8).click().perform()
            except BaseException:
                step -= 1
                continue
            else:
                time.sleep(0.1)
                step += 1
        print('点击预约\n')
        if step == 8:
            try:
                button9 = browser.find_element_by_xpath('//*[@id="reserveBtn"]')  # 点击“预约”
                ActionChains(browser).move_to_element(button9).click().perform()
            except BaseException:
                step -= 1
                continue
            else:
                step += 1
                time.sleep(0.1)
                break
    print('预约成功\n')


s = develop_strategy()
seat_num = get_seat_num()
account = sets.planning[0]
success_log = [0, 0, 0]
chrome = []
try:
    for i in range(len(s)):
        tx = 0
        while tx < 3:  # 防止登陆失败，尝试三次登录
            try:
                chrome.append(open_chrome("http://seatlib.hpu.edu.cn/login?targetUri=%2F"))
                time.sleep(2)
                sign_in(chrome[-1], account[i][0], account[i][1])
                time.sleep(1)
                reliable_find(chrome[-1], 3, '/html/body/div[4]/div[1]/ul/li[3]/a')
            except BaseException:
                tx += 1
                print(str(i + 1) + '号登录失败\n')
                print('正在尝试重新登录第' + str(i + 1) + '个号\n')
                if tx < 3:
                    chrome[-1].quit()  # 关闭浏览器
                    chrome.pop()
            else:
                break
    print('正在倒计时\n')
    timing('19:30')
    print('冲冲冲\n')
    threads = []
    for i in range(len(s)):
        print('第' + str(i + 1) + '个号:\n')
        chrome[i].refresh()
        time.sleep(0.2)
        t = threading.Thread(target=layout_and_seat_selection, args=(chrome[i], seat_num, s[i][0], s[i][1], 5))
        t.start()
        threads.append(t)
    for thread in threads:
        thread.join()
    end_time = time.strftime(" %H:%M:%S")
    for i in range(len(s)):
        try:
            chrome[i].find_element_by_xpath(
                '/html/body/div[3]/div[3]/div/div/dl/dd[*]/span[contains(text(), "支持环保，拍照有效")]')
        except BaseException:
            success_log[i] = 0
        else:
            success_log[i] = 1
            print(str(i + 1) + '号浏览器截图\n')
            chrome[i].save_screenshot(sets.file_path + 'success' + str(i + 1) + '.png')  # 截图
    send_p = []
    send_m = ''
    for i in range(len(s)):
        if success_log[i] == 1:
            send_p.append(sets.file_path + 'success' + str(i + 1) + '.png')
            send_m = send_m + str(i + 1) + '号执行成功 '
        else:
            send_m = send_m + str(i + 1) + '号执行失败 '
    time.sleep(3)
    if len(s) != 0:
        print('正在发送通知邮件\n')
        yag = yagmail.SMTP(user=sets.email, password=sets.email_password, host="smtp.163.com")  # 创建SMTP对象
        content = [
            time.strftime("%Y/%m/%d") + end_time + '\n' + send_m + '\n凭证见附件'
        ]
        yag.send(to=sets.rec_email, subject="图书馆预约情况", contents=content, attachments=send_p)
        yag.close()  # 关闭连接
        print('发送成功\n')
except BaseException:
    print("执行异常\n")
finally:
    for i in range(len(s)):
        print('正在关闭' + str(i + 1) + '号浏览器\n')
        chrome[i].quit()  # 关闭浏览器
