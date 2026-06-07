#include "shmRead.h"
#include <sys/types.h>
shmRead::shmRead(key_t shmkey, key_t msgkey, key_t semkey)
{
    this->shmaddr = nullptr;
    this->shmid = 0;    //???????id
    this->msgid = 0;    //???????id
    this->semid = 0;    //?????id
    this->recvbuf = { 0 };        //??????????????
    this->arr[BLOCKNUM] = { 0 };
    this->index = -1;        //????n?????
    this->buf[8192] = { 0 };    //?????????????????
    umask(0);
    //???????????
    shmid = shmget(shmkey, sizeof(arr) + sizeof(buf) * BLOCKNUM, IPC_CREAT | 0777);
    if (shmid == -1)
    {
        perror("shmget error");
        return;
    }
    //???????????
    msgid = msgget(msgkey, IPC_CREAT | 0777);
    if (msgid == -1)
    {
        perror("msgget error");
        return;
    }
    //??????????????????
    semid = sem_create(semkey, 1);
    if (semid < 0)
    {
        perror("sem_create error");
        return;
    }
}

int shmRead::sem_create(key_t key, int sem_num)
{
    int res = 0;
    umask(0);
    res = semget(key, sem_num, IPC_CREAT | 0666);
    if (res < 0)
    {
        perror("semget error");
    }
    return res;
}

int shmRead::sem_p(int semid, int semindex)
{
    int res = 0;
    struct sembuf buf = { static_cast<unsigned short>(semindex), -1, SEM_UNDO };
    res = semop(semid, &buf, 1);
    if (res < 0)
    {
        perror("sem_p error");
    }
    return res;
}

int shmRead::sem_v(int semid, int semindex)
{
    int res = 0;
    struct sembuf buf = { static_cast<unsigned short>(semindex), 1, SEM_UNDO };
    res = semop(semid, &buf, 1);
    if (res < 0)
    {
        perror("sem_p error");
    }

    return res;
}

void shmRead::read_shm(char* data)
{
    //??????????????????????????????
    ssize_t res = msgrcv(msgid, &recvbuf, sizeof(recvbuf), 1, 0);
    if (res < 0)
    {
        perror("msgrcv error");
    }
    else
    {
        index = atoi(recvbuf.mtext);
        cout << "?????????????????????????????:" << index << endl;
        sem_p(semid, 0);
        //??????????
        shmaddr = shmat(shmid, NULL, 0);
        char* base = static_cast<char*>(shmaddr);
        memcpy(&arr[index], base + index * sizeof(int), sizeof(int));
        if (arr[index] == 1)
        {
            //?????????????????
            memcpy(buf, base + sizeof(arr) + index * sizeof(buf), sizeof(buf));
            //memcpy(&fdArr[index], shmaddr + sizeof(arr) + sizeof(buf) * BLOCKNUM + index * sizeof(int), sizeof(int));
            memcpy(data, buf, sizeof(buf));
            // clientfd = fdArr[index];
             //fdArr[index] = 0;
             //memcpy(shmaddr + sizeof(arr) + sizeof(buf) * BLOCKNUM + index * sizeof(int), &fdArr[index], sizeof(int));
             //???????????????
            memset(base + sizeof(arr) + index * sizeof(buf), 0, sizeof(buf));
            //??????????????
            arr[index] = 0;
            memcpy(base + sizeof(int) * index, &arr[index], sizeof(int));
        }
        shmdt(shmaddr);
        sem_v(semid, 0);
    }
    //?????,?????????????????
    index = 0;
    bzero(&recvbuf, sizeof(recvbuf));
    bzero(buf, sizeof(buf));
    bzero(arr, sizeof(arr));
    //bzero(fdArr, sizeof(fdArr));
}
