#include "shmWrite.h"
shmWrite::shmWrite(key_t shmkey, key_t msgkey, key_t semkey)
{
    this->shmaddr = nullptr;
    this->shmid = 0;    //???????id
    this->msgid = 0;    //???????id
    this->semid = 0;    //?????id
    this->sendbuf = { 0 };        //??????????????
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

    sem_setval(semid, 0, 1);
    shmaddr = shmat(shmid, NULL, 0);
    bzero(static_cast<char*>(shmaddr), sizeof(arr) + sizeof(buf) * BLOCKNUM);
    shmdt(shmaddr);

}

//?????????
int shmWrite::sem_create(key_t key, int sem_num)
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
//??????????(????????)
int shmWrite::sem_setval(int semid, int semIndex, int value)
{
    union semun arg;
    arg.val = value;
    int res = semctl(semid, semIndex, SETVAL, arg);
    if (res < 0)
    {
        perror("semctl error");
    }
    return res;
}
//???????P????
int shmWrite::sem_p(int semid, int semindex)
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
//???????V????
int shmWrite::sem_v(int semid, int semindex)
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



void shmWrite::write_shm(char* data)
{
    memcpy(this->buf, data, sizeof(this->buf));
    sem_p(semid, 0);
    //???????????????
    //??????????
    shmaddr = shmat(shmid, NULL, 0);
    char* base = static_cast<char*>(shmaddr);
    memcpy(arr, base, sizeof(arr));
    //???????????????????????????
    for (int i = 0; i < BLOCKNUM; i++)
    {
        if (arr[i] == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        shmdt(shmaddr);
        sem_v(semid, 0);
        index = -1;
        bzero(&sendbuf, sizeof(sendbuf));
        bzero(arr, sizeof(arr));
        return;
    }
    cout << "?????????????????" << index << endl;
    //???????????????????
    memcpy(base + sizeof(arr) + index * sizeof(buf), buf, sizeof(buf));
    arr[index] = 1;
    memcpy(base + index * sizeof(int), &arr[index], sizeof(int));
    //memcpy(shmaddr + sizeof(arr) + sizeof(buf) * BLOCKNUM + index * sizeof(int), &fdArr[index], sizeof(int));
    //??????????
    shmdt(shmaddr);
    sem_v(semid, 0);
    cout << "???????????????,?????:" << index << endl;
    //???????????????????????????????????
    sendbuf.mtype = 1;
    sprintf(sendbuf.mtext, "%d", index);
    int res = msgsnd(msgid, &sendbuf, sizeof(sendbuf), 0);
    if (res < 0)
    {
        perror("msgsnd ???????");
    }
    else
    {
        cout << "index?????????????" << endl;
    }
    //?????,???????????????
    index = -1;
    bzero(&sendbuf, sizeof(sendbuf));
    bzero(arr, sizeof(arr));

}
