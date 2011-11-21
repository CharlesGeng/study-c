#电话薄
people = {
        'Bill Gunn':
        {
            'phone': '123456',
            'addr': 'Tianjin'
            },
        'Media Zhang':
        {
            'phone': '999999',
            'addr': 'Beijing'
            }
        }
#输出内容
lables = {
        'phone' : 'phone number',
        'addr'  : 'address'
        }
#用户名
name = input('Name:')
key = input('Phone number(p) or address(a):')
if key == 'p' : key = 'phone'
if key == 'a' : key = 'addr'
if name in people:
    print("%s %s is %s" % (name, lables[key], people[name][key]))
input('Press enter!')
