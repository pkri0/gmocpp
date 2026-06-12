import std.compat;

#include <cassert>

// GAMS
#include "gmomcc.h"
#include "gevmcc.h"

#define DllExport __declspec( dllexport )

typedef struct
{
   gmoHandle_t   gmo;
   gevHandle_t   gev;

} gamscpp_t;


int solve(gmoHandle_t gmo) {
    int n,m;
    n = gmoN(gmo);
    m = gmoM(gmo);

    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;

    return 0;
}

extern "C" DllExport int aaaCreate(void** Cptr, char* msgBuf, int msgBufLen);
int aaaCreate(
   void**   Cptr,
   char*    msgBuf,
   int      msgBufLen
)
{
   assert(Cptr != NULL);
   assert(msgBufLen > 0);
   assert(msgBuf != NULL);

   *Cptr = calloc(1, sizeof(gamscpp_t));

   msgBuf[0] = 0;

   if( !gmoGetReady(msgBuf, msgBufLen) )
      return 1;

   if( !gevGetReady(msgBuf, msgBufLen) )
      return 1;

   return 0;
}

extern "C" DllExport void aaaFree(void** Cptr);
void aaaFree(
   void** Cptr
)
{
   gamscpp_t* g;

   assert(Cptr != NULL);
   assert(*Cptr != NULL);

   g = (gamscpp_t*) *Cptr;

   free(g);

   /* free some thread-local global data */

   *Cptr = NULL;

   gmoLibraryUnload();
   gevLibraryUnload();
}

extern "C" DllExport int aaaReadyAPI(void* Cptr, gmoHandle_t Gptr);
int aaaReadyAPI(
   void*       Cptr,
   gmoHandle_t Gptr
)
{
   gamscpp_t* g;

   assert(Cptr != NULL);
   assert(Gptr != NULL);

   g = (gamscpp_t*) Cptr;
   g->gmo = Gptr;
   g->gev = (gevHandle_t) gmoEnvironment(g->gmo);


   return 0;
}

extern "C" DllExport int aaaCallSolver(void* Cptr);
int aaaCallSolver(
   void* Cptr
)
{
   gamscpp_t* g;

   g = (gamscpp_t*) Cptr;
   assert(g->gmo != NULL);
   assert(g->gev != NULL);
   /* solve the problem */
   solve(g->gmo); 
   /* pass solution, status, etc back to GMO */
   return 0;
}

#ifdef _WIN32
#include <windows.h>  /* to make sure that BOOL is defined */
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
        
            if (lpvReserved != nullptr)
            {
                break; // do not do cleanup if process termination scenario
            }
            
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
#endif
