/***************************************************************************
 *   Copyright (C) 2007 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PDF_FIELD_H_
#define _PDF_FIELD_H_

#include "PdfDefines.h"  

#include "PdfAnnotation.h"
#include "PdfName.h"
#include "PdfString.h"

namespace PoDoFo {

class PdfAcroForm;
class PdfAction;
class PdfAnnotation;
class PdfDocument;
class PdfObject;
class PdfPage;
class PdfRect;


/** The type of PDF field
 */
typedef enum EPdfField {
    ePdfField_Button, 
    ePdfField_Text,
    ePdfField_Choice,
    ePdfField_Signature,

    ePdfField_Unknown = 0xff
};


class PODOFO_API PdfField {
 protected:
    /** Create a new PdfAcroForm dictionary object
     *  \param pParent parent of this action
     */
    PdfField( EPdfField eField, PdfAnnotation* pWidget, PdfAcroForm* pParent );

    PdfField( EPdfField eField, PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    PdfField( EPdfField eField, PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

    /** 
     *  Set a bit in the field flags value of the fields dictionary.
     *
     *  \param lValue the value specifying the bits to set
     *  \param bSet if true the value will be set otherwise
     *              they will be cleared.
     *
     *  \see GetFieldFlag
     */
    void SetFieldFlag( long lValue, bool bSet );

    /**
     *  \param lValue it is checked if these bits are set
     *  \param bDefault the returned value if no field flags are specified
     *
     *  \returns true if given bits are set in the field flags
     *
     *  \see SetFieldFlag
     */
    bool GetFieldFlag( long lValue, bool bDefault ) const;

 public:
    /** Create a PdfAcroForm dictionary object from an existing PdfObject
     *	\param pObject the object to create from
     */
    PdfField( PdfObject* pObject );

    virtual ~PdfField() { }

    /** Get the page of this PdfField
     *
     *  \returns the page of this PdfField
     */
    inline PdfPage* GetPage() const;

    void SetFieldName( const PdfString & rsName );

    void SetAlternateName( const PdfString & rsName );

    void SetMappingName( const PdfString & rsName ); 


    inline void SetMouseEnterAction( const PdfAction & rAction );
    inline void SetMouseLeaveAction( const PdfAction & rAction );
    inline void SetMouseDownAction( const PdfAction & rAction );
    inline void SetMouseUpAction( const PdfAction & rAction );

    inline void SetFocusEnterAction( const PdfAction & rAction );
    inline void SetFocusLeaveAction( const PdfAction & rAction );

    inline void SetPageOpenAction( const PdfAction & rAction );
    inline void SetPageCloseAction( const PdfAction & rAction );

    inline void SetPageVisibleAction( const PdfAction & rAction );
    inline void SetPageInvisibleAction( const PdfAction & rAction );
    
    /** 
     * \returns the type of this field
     */
    inline EPdfField GetType() const;

 private:

    /** 
     *  Initialize this PdfField.
     *
     *  \param pParent parent acro forms dictionary
     */
    void Init( PdfAcroForm* pParent );

    void AddAlternativeAction( const PdfName & rsName, const PdfAction & rAction );

 protected:
    PdfObject*     m_pObject;
    PdfAnnotation* m_pWidget;

 private:
    EPdfField  m_eField;
};

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline PdfPage* PdfField::GetPage() const
{
    return m_pWidget->GetPage();
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetMouseEnterAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("E"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetMouseLeaveAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("X"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetMouseDownAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("D"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetMouseUpAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("U"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetFocusEnterAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("Fo"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetFocusLeaveAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("BI"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetPageOpenAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("PO"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetPageCloseAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("PC"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetPageVisibleAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("PV"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfField::SetPageInvisibleAction( const PdfAction & rAction )
{
    this->AddAlternativeAction( PdfName("PI"), rAction );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline EPdfField PdfField::GetType() const
{
    return m_eField;
}

class PODOFO_API PdfButton : public PdfField {
 protected:
    enum { ePdfButton_NoToggleOff      = 0x0004000,
           ePdfButton_Radio            = 0x0008000,
           ePdfButton_PushButton       = 0x0010000,
           ePdfButton_RadioInUnison    = 0x2000000
    };

    /** Create a new PdfButton
     */
    PdfButton( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfButton
     */
    PdfButton( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfButton
     */
    PdfButton( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

 public:

    /**
     * \returns true if this is a pushbutton
     */
    inline bool IsPushButton() const;

    /**
     * \returns true if this is a checkbox
     */
    inline bool IsCheckBox() const;

    /**
     * \returns true if this is a radiobutton
     */
    inline bool IsRadioButton() const;
};

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfButton::IsPushButton() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfButton_PushButton), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfButton::IsCheckBox() const
{
    return (!this->GetFieldFlag( static_cast<int>(ePdfButton_Radio), false ) &&
            !this->GetFieldFlag( static_cast<int>(ePdfButton_PushButton), false ) );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfButton::IsRadioButton() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfButton_Radio), false );
}


/** A push button is a button which has no state and value
 *  but can toggle actions.
 */
class PODOFO_API PdfPushButton : public PdfButton {
 public:
    /** Create a new PdfPushButton
     */
    PdfPushButton( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfPushButton
     */
    PdfPushButton( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfPushButton
     */
    PdfPushButton( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );


    void SetText( const PdfString & rsText );

 private:
    void Init();
};

/** A textfield in a PDF file.
 *  
 *  Users can enter text into a text field.
 *  Single and multi line text is possible,
 *  as well as richtext. The text can be interpreted
 *  as path to a file which is going to be submitted.
 */
class PODOFO_API PdfTextField : public PdfField {
 private:
    enum { ePdfTextField_MultiLine     = 0x0001000,
           ePdfTextField_Password      = 0x0002000,
           ePdfTextField_FileSelect    = 0x0100000,
           ePdfTextField_NoSpellcheck  = 0x0400000,
           ePdfTextField_NoScroll      = 0x0800000,
           ePdfTextField_Comb          = 0x1000000,
           ePdfTextField_RichText      = 0x2000000
    };

 public:
    /** Create a new PdfTextField
     */
    PdfTextField( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfTextField( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfTextField( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

    /** Sets the text contents of this text field.
     *
     *  \param rsText the text of this field
     */
    void SetText( const PdfString & rsText );

    /**
     *  \returns the text contents of this text field
     */
    PdfString GetText() const;

    /** Sets the max length in characters of this textfield
     *  \param nMaxLen the max length of this textfields in characters
     */
    void SetMaxLen( int nMaxLen );

    /** 
     * \returns the max length of this textfield in characters or -1
     *          if no max length was specified
     */
    int GetMaxLen() const;

    /**
     *  Create a multi-line text field that can contains multiple lines of text.
     *  \param bMultiLine if true a multi line field is generated, otherwise
     *                    the text field can contain only a single line of text.
     *
     *  The default is to create a single line text field.
     */
    inline void SetMultiLine( bool bMultiLine );

    /** 
     * \returns true if this text field can contain multiple lines of text
     */
    inline bool IsMultiLine() const;

    /** 
     *  Create a password text field that should not echo entered
     *  characters visibly to the screen.
     *
     *  \param bPassword if true a password field is created
     *
     *  The default is to create no password field
     */
    inline void SetPasswordField( bool bPassword );

    /**
     * \returns true if this field is a password field that does
     *               not echo entered characters on the screen
     */
    inline bool IsPasswordField() const;

    /** 
     *  Create a file selection field.
     *  The entered contents are treated as filename to a file
     *  whose contents are submitted as the value of the field.
     *
     *  \param bFile if true the contents are treated as a pathname
     *               to a file to submit
     */
    inline void SetFileField( bool bFile );

    /**
     * \returns true if the contents are treated as filename
     */
    inline bool IsFileField() const;

    /** 
     *  Enable/disable spellchecking for this text field
     *
     *  \param bSpellcheck if true spellchecking will be enabled
     *
     *  Text fields are spellchecked by default
     */
    inline void SetSpellcheckingEnabled( bool bSpellcheck );

    /** 
     *  \returns true if spellchecking is enabled for this text field
     */
    inline bool IsSpellcheckingEnabled() const;

    /** 
     *  Enable/disable scrollbars for this text field
     *
     *  \param bScroll if true scrollbars will be enabled
     *
     *  Text fields have scrollbars by default
     */
    inline void SetScrollBarsEnabled( bool bScroll );

    /** 
     *  \returns true if scrollbars are enabled for this text field
     */
    inline bool IsScrollBarsEnabled() const;

    /** 
     *  Divide the text field into max-len equal
     *  combs.
     *
     *  \param bCombs if true enable division into combs
     *
     *  By default coms are disabled. Requires the max len
     *  property to be set.
     *
     *  \see SetMaxLen
     *  TODO: DominikS MaxLen
     */
    inline void SetCombs( bool bCombs );

    /**
     * \returns true if the text field is divided in to equal combs
     */
    inline bool IsCombs() const;

    /**
     * Creates a richtext field.
     *
     * \param bRichText if true creates a richtext field
     *
     * By default richtext is disabled.
     */
    inline void SetRichText( bool bRichText );

    /** 
     * \returns true if this is a richtext text field
     */
    inline bool IsRichText() const;

 private:
    void Init();
};

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetMultiLine( bool bMultiLine )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_MultiLine), bMultiLine );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsMultiLine() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_MultiLine), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetPasswordField( bool bPassword )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_Password), bPassword );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsPasswordField() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_Password), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetFileField( bool bFile )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_FileSelect), bFile );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsFileField() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_FileSelect), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetSpellcheckingEnabled( bool bSpellcheck )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_NoSpellcheck), !bSpellcheck );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsSpellcheckingEnabled() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_NoSpellcheck), true );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetScrollBarsEnabled( bool bScroll )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_NoScroll), !bScroll );    
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsScrollBarsEnabled() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_NoScroll), true );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetCombs( bool bCombs )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_Comb), bCombs );        
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsCombs() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_Comb), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfTextField::SetRichText( bool bRichText )
{
    this->SetFieldFlag( static_cast<int>(ePdfTextField_RichText), bRichText);        
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfTextField::IsRichText() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfTextField_RichText), false );
}

/** A list of items in a PDF file.
 *  You cannot create this object directly, use
 *  PdfComboBox or PdfListBox instead.
 *  
 *  \see PdfComboBox 
 *  \see PdfListBox
 */
class PODOFO_API PdfListField : public PdfField {
 protected:
    enum { ePdfListField_Combo         = 0x0020000,
           ePdfListField_Edit          = 0x0040000,
           ePdfListField_Sort          = 0x0080000,
           ePdfListField_MultiSelect   = 0x0200000,
           ePdfListField_NoSpellcheck  = 0x0400000,
           ePdfListField_CommitOnSelChange = 0x4000000
    };

    /** Create a new PdfTextField
     */
    PdfListField( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfListField( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfListField( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

 public:

    //const PdfString & GetSelectedItem(); /// ???

    /**
     * Inserts a new item into the list
     *
     * @param rsValue the value of the item
     * @param rsDisplayName an optional display string that is displayed in the viewer
     *                      instead of the value
     */
    void InsertItem( const PdfString & rsValue, const PdfString & rsDisplayName = PdfString::StringNull );

    /** 
     * Removes an item for the list
     *
     * @param nIndex index of the item to remove
     */
    void RemoveItem( int nIndex );

    /** 
     * @param nIndex index of the item
     * @returns the value of the item at the specified index
     */
    const PdfString & GetItem( int nIndex ) const;

    /** 
     * @param nIndex index of the item
     * @returns the display text of the item or if it has no display text
     *          its value is returned. This call is equivalent to GetItem() 
     *          in this case
     *
     * \see GetItem
     */
    const PdfString & GetItemDisplayText( int nIndex ) const;

    /**
     * \returns the number of items in this list
     */
    int GetItemCount() const;

    /** Sets the currently selected item
     *  \param nIndex index of the currently selected item
     */
    void SetSelectedItem( int nIndex );

    /** Sets the currently selected item
     *
     *  \returns the selected item or -1 if no item was selected
     */
    int GetSelectedItem() const;
    
#if 0
    // TODO:
#error "Only allow these if multiselect is true!"
    void SetSelectedItems( ... );

    PdfArray GetSelectedItems() ;
#endif


    /** 
     * \returns true if this PdfListField is a PdfComboBox and false
     *               if it is a PdfListBox
     */
    inline bool IsComboBox() const;

    /** 
     *  Enable/disable spellchecking for this combobox
     *
     *  \param bSpellcheck if true spellchecking will be enabled
     *
     *  combobox are spellchecked by default
     */
    inline void SetSpellcheckingEnabled( bool bSpellcheck );
    
    /** 
     *  \returns true if spellchecking is enabled for this combobox
     */
    inline bool IsSpellcheckingEnabled() const;

    /**
     * Enable or disable sorting of items.
     * The sorting does not happen in acrobat reader
     * but whenever adding items using PoDoFo or another
     * PDF editing application.
     *
     * \param bSorted enable/disable sorting
     */
    inline void SetSorted( bool bSorted );

    /**
     * \returns true if sorting is enabled
     */
    inline bool IsSorted() const;

    /**
     * Sets wether multiple items can be selected by the
     * user in the list.
     *
     * \param bMulti if true multiselect will be enabled
     *
     * By default multiselection is turned off.
     */
    inline void SetMultiSelect( bool bMulti );

    /** 
     * \returns true if multi selection is enabled
     *               for this list
     */
    inline bool IsMultiSelect() const;

    inline void SetCommitOnSelectionChange( bool bCommit );
    inline bool IsCommitOnSelectionChange() const;
};

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfListField::IsComboBox() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_Combo), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfListField::SetSpellcheckingEnabled( bool bSpellcheck )
{
    this->SetFieldFlag( static_cast<int>(ePdfListField_NoSpellcheck), !bSpellcheck );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfListField::IsSpellcheckingEnabled() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_NoSpellcheck), true );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfListField::SetSorted( bool bSorted )
{
    this->SetFieldFlag( static_cast<int>(ePdfListField_Sort), bSorted );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfListField::IsSorted() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_Sort), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfListField::SetMultiSelect( bool bMulti )
{
    this->SetFieldFlag( static_cast<int>(ePdfListField_MultiSelect), bMulti );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfListField::IsMultiSelect() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_MultiSelect), false );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfListField::SetCommitOnSelectionChange( bool bCommit )
{
    this->SetFieldFlag( static_cast<int>(ePdfListField_CommitOnSelChange), bCommit );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfListField::IsCommitOnSelectionChange() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_CommitOnSelChange), false );
}

/** A combo box with a drop down list of items.
 */
class PODOFO_API PdfComboBox : public PdfListField {
 public:
    /** Create a new PdfTextField
     */
    PdfComboBox( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfComboBox( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfComboBox( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

    /**
     * Sets the combobox to be editable
     *
     * \param bEdit if true the combobox can be edited by the user
     *
     * By default a combobox is not editable
     */
    inline void SetEditable( bool bEdit );

    /** 
     *  \returns true if this is an editable combobox
     */
    inline bool IsEditable() const;

};

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfComboBox::SetEditable( bool bEdit )
{
    this->SetFieldFlag( static_cast<int>(ePdfListField_Edit), bEdit);        
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfComboBox::IsEditable() const
{
    return this->GetFieldFlag( static_cast<int>(ePdfListField_Edit), false );
}

/** A list box
 */
class PODOFO_API PdfListBox : public PdfListField {
 public:
    /** Create a new PdfTextField
     */
    PdfListBox( PdfAnnotation* pWidget, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfListBox( PdfPage* pPage, const PdfRect & rRect, PdfAcroForm* pParent );

    /** Create a new PdfTextField
     */
    PdfListBox( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

};

};

#endif // _PDF_ACRO_FORM_H__PDF_NAMES_TREE_H_