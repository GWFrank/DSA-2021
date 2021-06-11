#include <stdio.h>

#define MAX_L 100005
#define REM 10000007

typedef unsigned long long int ULL;

int matchG(int m_chars[], int g_chars[]) {
    for (int i=0; i<52; i++) {
        if (g_chars[i] == 0)
            continue;
        if (m_chars[i] < g_chars[i])
            return 0;
    }
    return 1;
}

int myStrcmp(char* s, int st1, int st2, int l) {
    for (int i=0; i<l; i++) {
        if (s[st1+i] != s[st2+i]) {
            return 0;
        }
    }
    return 1;
}

void printMail(char* m, int slice[], int m_len) {
    for (int i=0; i<m_len; i++) {
        if (slice[i])
            printf("|");
        printf("%c", m[i]);
    }
    printf("\n");
}

int charToInt(char c) {
    if (c >= 'A' && c <= 'Z')
        return c-'A';
    else
        return c-'a'+26;
}

int main(){
    // printf("Howdy!\n");
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        char mail[MAX_L], garbled[MAX_L];
        scanf("%s", mail);
        scanf("%s", garbled);
        // Remove garbled text
        int g_chars[52]={0};
        int j=0;
        while (garbled[j]) {
            g_chars[charToInt(garbled[j])]++;
            j++;
        }
        
        int m_l = 0, m_r = 0;
        int m_chars[52]={0};
        int g_len = MAX_L+10, st=-1, ed=-1;
        j=0;
        while (mail[j]) {
            m_chars[charToInt(mail[j])]++;
            while (matchG(m_chars, g_chars)) {
                // Record current segment
                if (m_r-m_l+1 < g_len) {
                    st = m_l; ed = m_r;
                    g_len = ed-st+1;
                }
                // Pop front
                m_chars[charToInt(mail[m_l])]--;
                m_l++;
            }
            m_r++;
            j++;
        }
        int m_len = j;
        if (st != -1) {
            int k;
            for (k=0; ed+1+k<m_len; k++) {
                mail[st+k] = mail[ed+1+k];
            }
            mail[st+k] = '\0';
        } else {
            g_len = 0;
        }
        m_len -= g_len;

        // Divide to blocks
        ULL base = 52;
        ULL base_pwr = 1;
        int slice[MAX_L]={0};
        int f_r = 0, f_l = 0;
        int b_r = m_len-1, b_l = m_len-1;
        ULL f_hash=0, b_hash=0;
        while (b_l > f_r) {
            f_hash = (base*f_hash + charToInt(mail[f_r]))%REM;
            b_hash = (b_hash + base_pwr*(charToInt(mail[b_l])))%REM;
            base_pwr = base_pwr*base%REM;
            if (f_hash == b_hash) {
                if (myStrcmp(mail, f_l, b_l, f_r-f_l+1)) {
                    slice[f_r+1] = 1;
                    slice[b_l] = 1;
                    f_l = f_r+1;
                    b_r = b_l-1;
                    f_hash = 0; b_hash = 0;
                    base_pwr = 1;
                }
            }
            f_r++;
            b_l--;
        }
        printMail(mail, slice, m_len);
    }
    return 0;
}