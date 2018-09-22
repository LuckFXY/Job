import multiprocessing as mp
import os
MAX_BLOCK_SIZE = 30000000


def Counter(name, mutex, block, word_map_list):
    
    print ('Run child process %s %s.....' % (name, os.getid()))
    for line in block:
        line = line.split(' ')
        for w in line:
            if w:
                if w not in word_map:
                    word_map[w] = 0
                word_map[w] += 1
    #mutex.acquire()
    
    #mutex.release()
    print("work_%d finished size = %d\n"%(name, len(word_map)))
    return word_map

def merge(word_map_list):
    sum_map = {}
    for wm in word_map_list:
        sum_map.update(wm)
    return sum_map



def topK(filename, k=10):
    word_map_list = []
    comm_word_map_list = mp.Manager().list(word_map_list)
    pool = mp.Pool(8)
    mutex = mp.Lock()
    try:
        with open(filename,'rb') as f:
            idx = 0
            block = f.readlines(MAX_BLOCK_SIZE)
            while block:
                block = [s.decode('utf-8','ignore')[:3] for s in block]
                print("start word_%d"%(idx))
                comm_block = mp.Manager().list(block)
                p = pool.apply_async ( Counter, args=(idx, mutex, block.copy(), comm_word_map_list) )
            
                
                idx += 1
                block = f.readlines(MAX_BLOCK_SIZE)
            
        pool.close()
        pool.join()
        print("1232")
        final_map = merge(comm_word_map_list)
        ret = sorted(final_map.items(), key = lambda item:item[1], reverse = True)[:k]
        print(ret)
        

    except Exception as e:
        print(e)

topK('test.txt')