#include <Array.h>
#include <stdio.h>
#include "vec3.h"

typedef struct ArchA ArchA;
struct ArchA {
    u8 signature;
    Array_vec3 pos;
    Array_vec3 vel;
    Array_vec3 trq;
};

typedef struct ArchB ArchB;
struct ArchB {
    u8 signature;
    Array_vec3 pos;
};

typedef struct ArchC ArchC;
struct ArchC {
    u8 signature;
    Array_vec3 pos;
    Array_vec3 vel;
};

typedef enum Signature Signature;
enum Signature {
    pos = 0b00000001,
    vel = 0b00000010,
    trq = 0b00000100,
};
#define KindCount 3
typedef union ArchetypeUnion ArchetypeUnion;
union ArchetypeUnion {
    ArchA archa;
    ArchB archb;
    ArchC archc;
};
typedef struct TaggedArchetype TaggedArchetype;
struct TaggedArchetype {
    Signature signature;
    ArchetypeUnion value;
};

bool queryTest(u8 a, u8 b) {
    return (a & b) == b;
}

Array_voidptr archetypeQuery(void *archs[], Signature signature) {
    Array_voidptr queryresults = {};
    for (i32 i = 0; i < 3; ++i) {
        u8 asignature = *((u8 *)(archs[i]));
        // printf("signature = %d\n", asignature);
        if (queryTest(asignature, signature)) {
            Array_voidptr_append(&queryresults, &archs[i]);
        }
    }
    return queryresults;
}

void systemIntegrate(Array_vec3 pos, Array_vec3 vel) {
    printf("ran\n");
    for (i32 i = 0; i < pos.length; ++i) {
        pos.data[i].x += vel.data[i].x;
        pos.data[i].y += vel.data[i].y;
        pos.data[i].z += vel.data[i].z;
    }
}

void Archetype_test() {
    ArchA a = {.signature = pos | vel | trq};
    ArchB b = {.signature = vel};
    ArchC c = {.signature = pos | vel};

    void *archetypes[3] = { &a, &b, &c };
    for (i32 i = 0; i < 3; ++i) {
        u8 signature = *((u8 *)(archetypes[i]));
        if (queryTest(signature, pos | vel)) {
            printf("signature hit = %d\n", signature);
            // systemIntegrate(archetypes[i], archetypes[i]);
        }
    }

    // Array_voidptr taggedarchetypequery = archetypeQuery(archetypes, pos | vel);
    // for (i32 i = 0; i < taggedarchetypequery.length; ++i) {
    //     u8 signature = *((u8 *)(archetypes[i]));
    //     printf("signature = %d\n", signature);
    //     if (queryTest(signature, pos | vel)) {
    //         printf("hit\n");
    //     }
    //     // switch (*((u8 *)(&archetypes[i]))) {
    //     //     case pos | vel | trq:
    //     //         // ArchA archa = *((ArchA *)taggedarchetypequery.data[i]);
    //     //         // systemPhysicalDistortion(archa.pos, archa.vel);
    //     //     break;
    //     //     case pos | vel: // this means collect all archs that have pos | vel
    //     //         ArchC archc = *((ArchC *)taggedarchetypequery.data[i]);
    //     //         systemIntegrate(archc.pos, archc.vel);
    //     //     break;
    //     //     case vel:
    //     //     break;
    //     // }
    // }
    // printf("query length = %llu\n", taggedarchetypequery.length);
}
