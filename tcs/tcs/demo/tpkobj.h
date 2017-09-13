/// \file tpkobj.h
/// \brief Implements a template class for tpk object stored in hash tables

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkTPKOBJ_H
#define dpkTPKOBJ_H

#include <tcl.h>
#include <tpk.h>

template <typename T>

/// Template class for custom Tcl object types.
/**
    TpkObj's cannot be static because they cannot be constucted until
    Tcl has been initialised.
*/
class TpkObj {
    private:

    // No copy constructor or assignment operator
        TpkObj(const TpkObj&);
        TpkObj& operator=(const TpkObj&);

    // Count of objects; used to create unique names.
        int Count;

    // Object epoch. This is incremented whenever an object is delete and
    // is used to detect when a internal representation is potentially
    // invalid because the object has been deleted.
        int Epoch;

    // Tcl ObjType
        Tcl_ObjType ObjType;

    // Hash table
    public:
        Tcl_HashTable table;

    public:
    /// Custom ObjType
        typedef struct Tpk_Obj {
            Tcl_Interp* interp;
            Tcl_Obj* objPtr;
            Tcl_HashEntry* hashPtr;
            T* obj;
        } Tpk_Obj;

    /// Constructor
        TpkObj(
            char* name      ///< Object type name
        ) {

        // Initialize the Tcl ObjType.
            ObjType.name = new char[strlen(name)+1];
            strcpy(ObjType.name, name);
            ObjType.freeIntRepProc = NULL;
            ObjType.dupIntRepProc = NULL;
            ObjType.updateStringProc = NULL;
            ObjType.setFromAnyProc = NULL;

        // Initialise the hash table
            Tcl_InitHashTable( &table, TCL_STRING_KEYS );

            Count = 0;
            Epoch = 0;
        }

    /// Destructor.
        ~TpkObj() {
            delete[] ObjType.name;
            Tcl_DeleteHashTable(&table);
        }

    /// Add new object.
        Tpk_Obj* NewObj( 
            Tcl_Interp* interp,     ///< Tcl interpreter
            T* obj,                 ///< New object
            Tcl_Obj* name           ///< Object name
        ) {


        // Allocate pointing object structure.
            Tpk_Obj* objStruct = new Tpk_Obj;

        // Create handle string.
            int create;
            Tcl_HashEntry* entryPtr = NULL;
            Tcl_Obj* handleObj = name;
            if ( handleObj ) {

            // Name is specified.
                entryPtr = Tcl_CreateHashEntry( &table,
                        Tcl_GetStringFromObj( handleObj, 0 ), &create);
                if ( ! create ) {
                    Tcl_ResetResult(interp);
                    Tcl_AppendResult( interp, ObjType.name, " already exists", NULL);
                    return NULL;
                }
            } else {

            // Construct unique name
                char handleName[16 + TCL_INTEGER_SPACE];
                while ( entryPtr == 0 ) {
                    sprintf( handleName, "%s%d", ObjType.name, Count++ );
                    handleObj = Tcl_NewStringObj( handleName, -1 );
                    entryPtr = Tcl_CreateHashEntry( &table, handleName, &create);
                }
            }

        // Create Tcl object and store pointers in the internal representation.
            handleObj->typePtr = &ObjType;
            handleObj->internalRep.twoPtrValue.ptr1 = objStruct;
            handleObj->internalRep.twoPtrValue.ptr2 =
                    reinterpret_cast<void*>(Epoch);

        // Setup structure.
            objStruct->interp = interp;
            objStruct->objPtr = handleObj;
            objStruct->obj = obj;

        // Store in hash table.
            Tcl_SetHashValue( entryPtr, objStruct);

        // Store pointer to hash entry.
            objStruct->hashPtr = entryPtr;

        // Set Tcl result to the handle.
            Tcl_SetObjResult( interp, handleObj);

        // Return pointer to new struct.
            return objStruct;
        }

    /// Get object from TclObj
        Tpk_Obj* GetObj( 
            Tcl_Interp* interp,     ///< Tcl interpreter
            Tcl_Obj* objPtr         ///< Tcl Obj
        ) {

        // Check that the Tcl obj has the right type and epoch.
            if (objPtr->typePtr != &ObjType ||
                    reinterpret_cast<int>(objPtr->internalRep.twoPtrValue.ptr2)
                    != Epoch ) {

            // Need to fetch the object from the hash table.
                char* name;
                Tpk_Obj* obj;
                Tcl_HashEntry* entryPtr;
                name = Tcl_GetString( objPtr );
                entryPtr = Tcl_FindHashEntry( &table, name);

            // Name not found
                if ( !entryPtr ) {
                    if ( interp ) {
                        Tcl_Obj *resultObj = Tcl_GetObjResult( interp );
                        Tcl_AppendStringsToObj( resultObj, "invalid ",ObjType.name,
                                " \"", name, "\"", (char*)NULL );
                    }
                    return NULL;
                }

            // Store internal representation.
                obj = static_cast<Tpk_Obj*>(Tcl_GetHashValue( entryPtr ));
                objPtr->typePtr = &ObjType;
                objPtr->internalRep.twoPtrValue.ptr1 = obj;
                objPtr->internalRep.twoPtrValue.ptr2 =
                        reinterpret_cast<void*>(Epoch);
            }

        // Return pointer to object.
            return (Tpk_Obj*)objPtr->internalRep.twoPtrValue.ptr1;
        }

    /// Free object
        int FreeObj( 
            Tcl_Interp* interp,     ///< Tcl interpreter
            Tpk_Obj* obj            ///< object
        ) {

        // Free the object.
            delete (T*)obj->obj;

        // Delete hash table entry.
            Tcl_DeleteHashEntry( obj->hashPtr );

        // Free the struct.
            delete obj;

        // Increment the epoch.
            Epoch++;

            return TCL_OK;
        }
};

#endif

