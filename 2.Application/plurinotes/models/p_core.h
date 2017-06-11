#ifndef P_CORE
#define P_CORE

#include "main.h"
#include "p_notes.h"
#include "p_xml.h"

class PluriNotes {

    private:
        ActiveNotesManager* activeNotesManager;
        ArchivedNotesManager* archivedNotesManager;
        DeletedNotesManager* deletedNotesManager;
        XMLManager* xmlManager;

    public:
        PluriNotes();
        ~PluriNotes();

        ActiveNotesManager* getActiveNotesManager() const { return activeNotesManager; }
        ArchivedNotesManager* getArchivedNotesManager() const { return archivedNotesManager; }
        DeletedNotesManager* getDeletedNotesManage() const { return deletedNotesManager; }
        XMLManager* getXMLManager() const { return xmlManager; }
        Note* getNoteByID(QString);
};

#endif // P_CORE
