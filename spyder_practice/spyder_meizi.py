import requests
from bs4 import BeautifulSoup as bs
import os
import random
import urllib
from lxml import etree
import time
import threading
class MZitu():
    def __init__(self, baseURL=None, pages=None):
        self.baseURL = "http://www.mzitu.com"
        self.pages = pages
        self.download_path = "E:\meizi"
        self.UserAgent_List = []
        with open("user_agent.txt",'r') as f:
            for line in f.readlines():
                line = line.strip()
                self.UserAgent_List.append(line)
        assert len(self.UserAgent_List) != 0 , "user_agent_list is null"
        print("The number of user agent is %d"%(len(self.UserAgent_List)))
        self.userAgent = random.choice(self.UserAgent_List)
        self.head ={
            'Accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8",
            'Accept-Encoding': "gzip, deflate",
            'Accept-Language': "zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7",
            'Connection': "keep-alive",
            'DNT': "1",
            'Host': "www.mzitu.com",
            'Upgrade-Insecure-Requests': "1",
            'User-Agent': self.userAgent
        }
        
    def changeUserAgent(self):
        random.choice(self.UserAgent_List)
    
    def getHeader(self, referer):
        headers = {
            'User-Agent': random.choice(self.UserAgent_List),
            'Connection': 'keep-alive',
            'Referer': '{}'.format(referer)
        }
        return headers

    def getAtlasURL(self, page = 1):
        urlMain = '/'.join([self.baseURL,'page',str(page)])
        print(urlMain)
        print(self.head)
        resMain = requests.get(urlMain, headers = self.head)
        resMain.encoding = 'utf-8'
        selectorMain = etree.HTML(resMain.text)
        urls = []
        print(resMain.headers)

        for url in selectorMain.xpath('//*[@id="pins"]/li/a/@href'):
            urls.append(url)

        return urls

    def getAtlasPic(self, atlas_url, job_id = '0'):
        
        #get count
        request_page = requests.get(atlas_url, self.head)
        selector = etree.HTML(request_page.text)
        row = selector.xpath('//div[@class="pagenavi"]/a[last()-1]/@href')[0]
        count = int(row.split('/')[-1])
        
        #create the folder to save the pictures
        _folder_name = atlas_url.split('/')[-1]
        folder_name = os.path.join(self.download_path, _folder_name)

        if not os.path.exists(folder_name): 
            os.mkdir(folder_name)
        print("\n----------worker=%s, The target folder : %s"%(job_id, folder_name)) 
        #write log file 
        info = "There are %d pictures in %s"%(count, _folder_name)
        with open("plan.txt","a+") as f:
            f.write(info+'\r\n')
        print("worker %s: %s"%(job_id, info))
        #download pictures page by page in Atlas
        header_pic= self.getHeader(referer = atlas_url)
        i = 1
        wait_count = 1
        while i < count:
            page_pic_url = atlas_url + '/' + str(i)
            if i != 1:
                rq_page_pic = requests.get(page_pic_url, header_pic)
                selector = etree.HTML(rq_page_pic.text)
            pic_src = selector.xpath('//div[@class="main-image"]//img/@src')
            try:
                pic_src = pic_src[0]
            except IndexError:
                print("pic_src=",pic_src)
                print(page_pic_url)
                rq_page_pic = requests.get(page_pic_url, header_pic)
                selector = etree.HTML(rq_page_pic.text)
                pic_src = selector.xpath('//div[@class="main-image"]//img/@src')
                if not pic_src:
                    info = "\n Nooooooooo worker=%s download %s failed at no.%d"%(job_id, atlas_url, i)
                    with open("error_log.txt","a+") as f:
                        f.write(info)
                    print(info)
                    break
            pic_name = ''.join(pic_src.split('/')[-3:])
            pic_name = os.path.join(folder_name, pic_name)
            if os.path.exists(pic_name):
                print("%s exist"%(pic_name))
                i += 1
                continue
            print('id=%s, No.%3d img=%s'%(job_id, i,pic_src))
            
            time.sleep(random.randint(2,10))
            try:
                request_img = requests.get(pic_src, headers = header_pic, timeout=4)
                i += 1

                with open(pic_name,"wb") as f:
                    f.write(request_img.content)
                print("id=%s, No.%d finished!"%(job_id, i))
                
            except Exception as e:
                #print(e)
                header_pic= self.getHeader(referer = atlas_url)
                wait_time = random.randint(4,8)* wait_count
                # print("\n worker=%s meet error at %d, after %d seconds restart\n new_head=%s"
                #     %(job_id, i, wait_time, header_pic)
                #     )
                print("(@_@) worker=%s meet error at %d, after %d seconds restart\n "
                     %(job_id, i, wait_time)
                     )
                time.sleep(wait_time)
                if wait_count < 33:
                    wait_count = 2
                rq = requests.get(atlas_url, self.head)
                
                print('Connection status: ', rq.headers['Connection'])
        print("(^.^) worker=%s has been finished"%(job_id))


mz = MZitu()
#mz.getAtlasPic("http://www.mzitu.com/99566")
candidate = [
    '99566','48149','101498','117874','21618','68870','131887','131616','122284',
    '103328','97462','129128','123576','8474','20290','90056','63289','99666',
    '40276','110847','70747','34340','57875','5257','43424','94993','34766'
]
candidate = candidate[2:]
worker_list = []
j = 0
def test(id):
    for i in range(10):
        print("id=%d i=%d"%(id, i))
        time.sleep(1)
for c in candidate:
    atlas_url = '/'.join([mz.baseURL,c])
    job_id = "W.%d_%s"%(j, c)
    j += 1
    t = threading.Thread(target=mz.getAtlasPic, args=(atlas_url,job_id))
    #t = threading.Thread(target=test, args=(j,))
    worker_list.append(t)
    t.start()
    #t.join()

print("over")