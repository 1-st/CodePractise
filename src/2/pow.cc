#include <openssl/sha.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
//将无符号字符类型定义为byte(0-255)(uint8)
typedef unsigned char byte;
//定义挖矿的难度(256BitHash前置0位数)
short int Hard = 15;

uint64_t MaxNonce = UINT64_MAX;
// 极简块结构
struct Block {
  byte prevHash[SHA256_DIGEST_LENGTH];
  byte transactionHash[SHA256_DIGEST_LENGTH];
  byte hash[SHA256_DIGEST_LENGTH];
  uint64_t nonce;
};
// 将uint64类型数据存储在byte[8]数组中
void Uint64ToByte(uint64_t uin, byte *b_ret /*8 bytes 64 bits*/) {
  for (int i = 7; i >= 0; i--) {
    b_ret[7 - i] = (byte)(uin >> (i * 8));
  }
}
//将长度为len的byte[]做hash
void ByteSha256(void *str, byte *hash_ret, int len) {
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str, len);
  SHA256_Final(hash_ret, &sha256);
}
//按二进制输出制定长度的byte数组
void PrintByteBin(byte *hash, int len) {
  for (int i = 0; i < len; i++) {
    // _print_hash_b(hash[i]);
    for (int j = 7; j >= 0; j--) {
      if (hash[i] & (1 << j)) {
	printf("1");
      } else {
	printf("0");
      }
    }
  }
}
// 按16进制输出指定长度的byte数组
void PrintByteHex(byte *hash, int len) {
  for (int i = 0; i < len; i++) {
    int low = hash[i] & 0x0F;
    printf("%x", hash[i] >> 4);
    printf("%x", low);
  }
}
// 在两个byte数组之间复制数据
void ByteCopy(byte *from, byte *to, int fromLow, int toLow, int len) {
  for (int i = 0; i < len; i++) {
    to[toLow + i] = from[fromLow + i];
  }
}
//比较两个相同长度的byte数组
// example ByteBigger([00110000,11111111],[01000000,00000000])=>false
bool ByteBiggerOrEqual(byte *me, byte *other, int len) {
  for (int i = 0; i < len; i++) {
    if (me[i] < other[i]) {
      return false;
    } else if (me[i] == other[i]) {
      continue;
    } else {
      return true;
    }
  }
  return true;  //等于
}
void Block_PrepareData(Block *b, byte *hash_ret) {
  byte temp[32 + 32 + 8]{};
  ByteCopy(b->prevHash, temp, 0, 0, 32);
  ByteCopy(b->transactionHash, temp, 0, 32, 32);
  byte nonceHash[8];
  Uint64ToByte(b->nonce, nonceHash);
  ByteCopy(nonceHash, temp, 0, 64, 8);
  ByteSha256((void *)temp, hash_ret, 72);
}
void Block_RunPoW(Block *b) {
  byte targetHash[32];
  {  //产生目标Hash
    int emptyByteCount = Hard / 8;
    int remainderBits = Hard - emptyByteCount;
    for (int i = 0; i < emptyByteCount; i++) {
      targetHash[i] = 0x00;
    }
    if (remainderBits != 0) {
      targetHash[emptyByteCount] >>= remainderBits;
    }
  }
  byte hash[32];
  printf("\nMining:\n");
  while (b->nonce < MaxNonce) {
    Block_PrepareData(b, hash);
    if (b->nonce % 10000 == 0) {
      PrintByteHex(hash, 32);
      printf("\r");
    }
    if (ByteBiggerOrEqual(hash, targetHash, 32) == false) {
      printf("\n\nDone!\n\n");
      ByteCopy(hash, b->hash, 0, 0, 32);
      PrintByteHex(b->hash, 32);
      break;
    }
    if (b->nonce + 1 == MaxNonce) {
      b->nonce = 0;
    } else {
      b->nonce++;
    }
  }
}
int main() {
  byte PrevHash[SHA256_DIGEST_LENGTH];
  byte TransactionHash[SHA256_DIGEST_LENGTH];
  ByteSha256((void *)"example:prev", PrevHash, 12);
  ByteSha256((void *)"example:tran", TransactionHash, 12);
  Block b{};
  ByteCopy(PrevHash, b.prevHash, 0, 0, 32);
  ByteCopy(TransactionHash, b.transactionHash, 0, 0, 32);
  b.nonce = 0;
  printf("prev hash:");
  PrintByteHex(b.prevHash, 32);
  printf("\n");
  PrintByteBin(b.prevHash, 32);
  printf("\n");
  printf("transaction hash:");
  PrintByteHex(b.transactionHash, 32);
  printf("\n");
  PrintByteBin(b.transactionHash, 32);
  printf("\n");
  Block_RunPoW(&b);
  return 0;
}

