def num(s):
    try:
        return int(s)
    except ValueError:
        return round(float(s),1)

def parseString(string):
    '''將題目的字串轉成list of Polynomial物件s'''

    def scanOperator(string):
        '''Find the index of '+' or '-'. Complexity = O(n).'''
        operator_idx = list()
        for i in range(len(string)):
            if string[i] == '-':
                operator_idx.append({'idx': i, 'positive': False})
            elif string[i] == '+':
                operator_idx.append({'idx': i, 'positive': True})
        return operator_idx

    def splitPolyStr(string, operator_idx):
        '''Divid huge string into list of substings. Ex:['+5.5x^5', '+3x^3', '+1']. Complexity = O(n).'''
        polystr_lst = list()
        for i, v in enumerate(operator_idx):
            if i != (len(operator_idx)-1):
                begin = operator_idx[i]['idx']
                end = operator_idx[i+1]['idx']
                substr = string[begin:end]
                polystr_lst.append(substr)
            else: # last operation
                begin = operator_idx[i]['idx']
                substr = string[begin:]
                polystr_lst.append(substr)
        return polystr_lst

    # String must start with '+' or '-'.
    if string[0] != '-':
        string = "+"+string
    print(string)

    # Divid origin full-string into a list of sub-string. # ['-2.6x^3', '+4.9']
    operator_idx = scanOperator(string)
    substr_lst = splitPolyStr(string, operator_idx)
    print(operator_idx)
    print(substr_lst)

    # Parse sub-stings into objects.
    lst = list()
    for i, v in enumerate(substr_lst): # v = '-2.6x^3' or '+1'
        # Positive / negative
        positive = True if v[0] == '+' else False
        v = v[1:]

        # 判斷指數係數
        coef, exp = 0, 0
        if v.find('x^') != -1:
            # Expon not 0
            content = v.split('x^') #'x^1' > ['', '1'] #'2.6x^3' > ['2.6', '3'] 
            if len(content[0]):
                # Coef not 1
                exp  = num(content[1])
                coef = num(content[0])
            else:
                # Coef is 1
                exp  = num(content[1])
                coef = 1
        else:
            # v is 常數項(constant), expon is 0
            coef = num(v)
            
        if not positive:
            coef = (-coef)
        # newpoly = Polynomial(coef, exp)
        # lst.append(newpoly)
        print('coef:', coef, ' , exp:', exp)
        
    
    return lst

polyStr1 = "5x^5+3x^3+1"
polyStr2 = "4x^4+2x^2+x^1"
polyStr3 = "-2.6x^3+4.9"

# x = 'x^1'.split('x^')
# print(x)
# if len(x[0]):
#     print('if')
# else:
#     print('else')

# print('4.9'.find('x^'))

parseString(polyStr3)
