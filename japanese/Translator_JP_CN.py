'''
History:
2017.03.09 initial version of JP_ZH translator
'''
#/usr/bin/env python
#coding=utf-8

import http.client
import hashlib
import urllib
import random
import json
import time
import os

os.chdir('E:\ANKI')
fileName =  'JapaneseWordList.txt'
transFileName =  'TranslatedList.txt'

appid = '20170309000041915'
secretKey = 's3546J9Lqvq18D20otCV'


httpClient = None
myurl = '/api/trans/vip/translate'
fromLang = 'jp'
toLang = 'zh'


with open(fileName) as fp:
    try:
        httpClient = http.client.HTTPConnection('api.fanyi.baidu.com')
        transFile = open(transFileName,encoding='utf8', mode='w')
        for line in iter(fp.readline, ''):
            time.sleep(0.2)
            q = line
            salt = random.randint(32768, 65536)

            sign = appid + q+str(salt) + secretKey
            m1 = hashlib.md5()
            m1.update(sign.encode())
            sign = m1.hexdigest()
            myurl = myurl+'?appid='+appid+'&q=' + urllib.parse.quote(q) + '&from=' + fromLang + '&to=' + toLang + '&salt=' + str(salt) + '&sign=' + sign

            httpClient.request('GET', myurl)

            #response是HTTPResponse对象
            response = httpClient.getresponse()
            info = json.loads(response.read())
            singleTranslation = str.format('{0},{1}', info['trans_result'][0]['src'], info['trans_result'][0]['dst'])
            print(singleTranslation)
            transFile.writelines(singleTranslation + os.linesep)
    except Exception as e:
            print(e)
    finally:
        if httpClient:
            httpClient.close()
        if transFile:
            transFile.close()

import winsound
i = 0
while i < 3:
    i = i + 1
    winsound.Beep(1024,50)
    time.sleep(0.2)
