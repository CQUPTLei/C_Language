#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PORT_GROUPS 10
#define MAX_PORTS 100


// �ȽϺ���������qsort����
int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}


// �ϲ������˿��飬ȷ���ϲ�����¶˿����в������ظ��˿ںţ�����С��������
void merge_port_groups(int* group1, int size1, int* group2, int size2, int* result, int* result_size) {
    // ��grup1�����еĶ˿ںŸ��Ƶ������
    for (int i = 0; i < size1; i++) 
        result[(*result_size)++] = group1[i];
    // ��gruppo2�в��ظ��Ķ˿ںŸ��Ƶ������
    for (int i = 0; i < size2; i++) {
        int found = 0;
        for (int j = 0; j < size1; j++) {
            if (group2[i] == group1[j]) {
                found = 1;
                break;
            }
        }
        if (!found)
            result[(*result_size)++] = group2[i];
    }
    // �Խ����������
    qsort(result, *result_size, sizeof(int), cmp);
}

int main() {
    int m;
    scanf("%d", &m);

    // �洢��������
    int port_groups[MAX_PORT_GROUPS][MAX_PORTS] = { 0 };
    int port_group_sizes[MAX_PORT_GROUPS] = { 0 };

    // ��ȡ��������
    for (int i = 0; i < m; i++) {
        char line[MAX_PORTS * 3];
        scanf("%s", line);

        char* token = strtok(line, ",");
        while (token != NULL) {
            port_groups[i][port_group_sizes[i]++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    // �洢�ϲ���Ķ˿���
    int merged[MAX_PORT_GROUPS][MAX_PORTS] = { 0 };
    int merged_sizes[MAX_PORT_GROUPS] = { 0 };
    int merged_count = 0;

    // ���������ݸ��Ƶ�merged������
    for (int i = 0; i < m; i++) {
        if (port_group_sizes[i] == 0) continue;

        memcpy(merged[merged_count], port_groups[i], sizeof(int) * port_group_sizes[i]);
        merged_sizes[merged_count] = port_group_sizes[i];
        merged_count++;
    }

    // �����ϲ��˿��飬ֱ��û���µĶ˿�����Ժϲ�Ϊֹ
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < merged_count; i++) {
            if (merged_sizes[i] == 0) continue;

            for (int j = i + 1; j < merged_count; j++) {
                if (merged_sizes[j] == 0) continue;
                // ���������˿���֮��Ĺ����˿���
                int common_ports = 0;
                for (int k = 0; k < merged_sizes[i]; k++) {
                    for (int l = 0; l < merged_sizes[j]; l++) {
                        if (merged[i][k] == merged[j][l]) common_ports++;
                    }
                }
                // �����˿�������2��ϲ�
                if (common_ports >= 2) {
                    int new_merged[MAX_PORTS] = { 0 };
                    int new_merged_size = 0;
                    merge_port_groups(merged[i], merged_sizes[i], merged[j], merged_sizes[j], new_merged, &new_merged_size);
                    memcpy(merged[i], new_merged, sizeof(int) * new_merged_size);
                    merged_sizes[i] = new_merged_size;
                    merged_sizes[j] = 0;
                    changed = 1;
                }
            }
        }
    }
    // ������
    printf("[");
    for (int i = 0; i < merged_count; i++) {
        if (merged_sizes[i] == 0) continue;

        printf("[");
        for (int j = 0; j < merged_sizes[i]; j++) {
            printf("%d", merged[i][j]);
            if (j != merged_sizes[i] - 1) printf(",");
        }
        printf("]");
        if (i != merged_count - 1) printf(",");
    }
    printf("]\n");

    return 0;
}