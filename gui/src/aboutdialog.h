#ifndef _GTKMM_ABOUTDIALOG_H
#define _GTKMM_ABOUTDIALOG_H

//
// This was copied from gtkmm 2.10.6 and hacked up a bit, so
// that we have a dialog class for systems using older
// versions of gtkmm24.  Debian stable, I'm looking at you...
//
// Chris Frey <cdfrey@foursquare.net>
//

#include <glibmm.h>

/* aboutdialog.h
 *
 * Copyright (C) 2004 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm/dialog.h>
//#include <glibmm/listhandle.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkAboutDialog GtkAboutDialog;
typedef struct _GtkAboutDialogClass GtkAboutDialogClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class AboutDialog_Class; } // namespace Gtk
namespace Gtk
{

/** The AboutDialog offers a simple way to display information about a program like its logo, name, copyright, 
 * website and license. It is also possible to give credits to the authors, documenters, translators and artists 
 * who have worked on the program. An about dialog is typically opened when the user selects the About option 
 * from the Help menu. All parts of the dialog are optional.
 *
 * About dialogs often contain links and email addresses. Gtk::AboutDialog supports this by offering global 
 * hooks, which are called when the user clicks on a link or email address, see set_email_hook() and 
 * set_url_hook(). Email addresses in the authors, documenters and artists properties are recognized by looking 
 * for <user@host>, URLs are recognized by looking for http://url, with the URL extending to the next space, 
 * tab or line break.
 *
 * @ingroup Dialogs
 */

class AboutDialog : public Dialog
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AboutDialog CppObjectType;
  typedef AboutDialog_Class CppClassType;
  typedef GtkAboutDialog BaseObjectType;
  typedef GtkAboutDialogClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~AboutDialog();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class AboutDialog_Class;
  static CppClassType aboutdialog_class_;

  // noncopyable
  AboutDialog(const AboutDialog&);
  AboutDialog& operator=(const AboutDialog&);

protected:
  explicit AboutDialog(const Glib::ConstructParams& construct_params);
  explicit AboutDialog(GtkAboutDialog* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkAboutDialog*       gobj()       { return reinterpret_cast<GtkAboutDialog*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkAboutDialog* gobj() const { return reinterpret_cast<GtkAboutDialog*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

  //Default Signal Handlers::
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:

  
public:
  AboutDialog();

  
  /** Returns the program name displayed in the about dialog.
   * @return The program name. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_name() const;
  
  /** Sets the name to display in the about dialog. 
   * If this is not set, it defaults to Glib::get_application_name().
   * 
   * @newin2p6
   * @param name The program name.
   */
  void set_name(const Glib::ustring& name);
  
  /** Returns the version string.
   * @return The version string. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_version() const;
  
  /** Sets the version string to display in the about dialog.
   * 
   * @newin2p6
   * @param version The version string.
   */
  void set_version(const Glib::ustring& version);
  
  /** Returns the copyright string.
   * @return The copyright string. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_copyright() const;
  
  /** Sets the copyright string to display in the about dialog.
   * This should be a short string of one or two lines. 
   * 
   * @newin2p6
   * @param copyright The copyright string.
   */
  void set_copyright(const Glib::ustring& copyright);
  
  /** Returns the comments string.
   * @return The comments. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_comments() const;
  
  /** Sets the comments string to display in the about 
   * dialog. This should be a short string of one or
   * two lines.
   * 
   * @newin2p6
   * @param comments A comments string.
   */
  void set_comments(const Glib::ustring& comments);
  
  /** Returns the license information.
   * @return The license information. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_license() const;
  
  /** Sets the license information to be displayed in the secondary
   * license dialog. If @a license  is <tt>0</tt>, the license button is
   * hidden.
   * 
   * @newin2p6
   * @param license The license information or <tt>0</tt>.
   */
  void set_license(const Glib::ustring& license);
  
  /** Returns the website URL.
   * @return The website URL. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_website() const;
  
  /** Sets the URL to use for the website link.
   * 
   * @newin2p6
   * @param website A URL string starting with "http://".
   */
  void set_website(const Glib::ustring& website);
  
  /** Returns the label used for the website link.
   * @return The label used for the website link. The string is owned by the about
   * dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_website_label() const;
  
  /** Sets the label to be used for the website link.
   * It defaults to the website URL.
   * 
   * @newin2p6
   * @param website_label The label used for the website link.
   */
  void set_website_label(const Glib::ustring& website_label);

   
  /** Returns the string which are displayed in the authors tab
   * of the secondary credits dialog.
   * @return A <tt>0</tt>-terminated string array containing
   * the authors. The array is owned by the about dialog 
   * and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::StringArrayHandle get_authors() const;

  
  /** Sets the strings which are displayed in the authors tab
   * of the secondary credits dialog. 
   * 
   * @newin2p6
   * @param authors A <tt>0</tt>-terminated array of strings.
   */
  void set_authors(const Glib::StringArrayHandle& authors) const;

  
  /** Returns the string which are displayed in the documenters 
   * tab of the secondary credits dialog.
   * @return A <tt>0</tt>-terminated string array containing
   * the documenters. The array is owned by the about dialog 
   * and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::StringArrayHandle get_documenters() const;

   
  /** Sets the strings which are displayed in the documenters tab
   * of the secondary credits dialog. 
   * 
   * @newin2p6
   * @param documenters A <tt>0</tt>-terminated array of strings.
   */
  void set_documenters(const Glib::StringArrayHandle& documenters);
  
  /** Returns the string which are displayed in the artists tab
   * of the secondary credits dialog.
   * @return A <tt>0</tt>-terminated string array containing
   * the artists. The array is owned by the about dialog 
   * and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::StringArrayHandle get_artists() const;
  
  /** Sets the strings which are displayed in the artists tab
   * of the secondary credits dialog. 
   * 
   * @newin2p6
   * @param artists A <tt>0</tt>-terminated array of strings.
   */
  void set_artists(const Glib::StringArrayHandle& artists);
  
  /** Returns the translator credits string which is displayed
   * in the translators tab of the secondary credits dialog.
   * @return The translator credits string. The string is
   * owned by the about dialog and must not be modified.
   * 
   * @newin2p6.
   */
  Glib::ustring get_translator_credits() const;
  
  /** Sets the translator credits string which is displayed in
   * the translators tab of the secondary credits dialog.
   * 
   * The intended use for this string is to display the translator
   * of the language which is currently used in the user interface.
   * Using gettext(), a simple way to achieve that is to mark the
   * string for translation:
   * @code
   * gtk_about_dialog_set_translator_credits (about, _("translator-credits"));
   * @endcode
   * It is a good idea to use the customary msgid "translator-credits" for this
   * purpose, since translators will already know the purpose of that msgid, and
   * since Gtk::AboutDialog will detect if "translator-credits" is untranslated
   * and hide the tab.
   * 
   * @newin2p6
   * @param translator_credits The translator credits.
   */
  void set_translator_credits(const Glib::ustring& translator_credits);

  
  /** Returns the pixbuf displayed as logo in the about dialog.
   * @return The pixbuf displayed as logo. The pixbuf is
   * owned by the about dialog. If you want to keep a reference
   * to it, you have to call Glib::object_ref() on it.
   * 
   * @newin2p6.
   */
  Glib::RefPtr<Gdk::Pixbuf> get_logo();
  
  /** Returns the pixbuf displayed as logo in the about dialog.
   * @return The pixbuf displayed as logo. The pixbuf is
   * owned by the about dialog. If you want to keep a reference
   * to it, you have to call Glib::object_ref() on it.
   * 
   * @newin2p6.
   */
  Glib::RefPtr<const Gdk::Pixbuf> get_logo() const;

  
  /** Sets the pixbuf to be displayed as logo in 
   * the about dialog. If it is <tt>0</tt>, the default
   * window icon set with Gtk::Window::set_default_icon()
   * will be used.
   * 
   * @newin2p6
   * @param logo A Gdk::Pixbuf, or <tt>0</tt>.
   */
  void set_logo(const Glib::RefPtr<Gdk::Pixbuf>& logo);

  
  /** Returns the icon name displayed as logo in the about dialog.
   * @return The icon name displayed as logo. The string is
   * owned by the dialog. If you want to keep a reference
   * to it, you have to call Glib::strdup() on it.
   * 
   * @newin2p6.
   */
  Glib::ustring get_logo_icon_name() const;
  
  /** Sets the pixbuf to be displayed as logo in 
   * the about dialog. If it is <tt>0</tt>, the default
   * window icon set with Gtk::Window::set_default_icon()
   * will be used.
   * 
   * @newin2p6
   * @param icon_name An icon name, or <tt>0</tt>.
   */
  void set_logo_icon_name(const Glib::ustring& icon_name);

  
  /** Returns whether the license text in @a about  is 
   * automatically wrapped.
   * @return <tt>true</tt> if the license text is wrapped 
   * 
   * @newin2p8.
   */
//  bool get_wrap_license() const;
  
  /** Sets whether the license text in @a about  is 
   * automatically wrapped.
   * 
   * @newin2p8
   * @param wrap_license Whether to wrap the license.
   */
//  void set_wrap_license(bool wrap_license);

  /** For instance,
   * void on_activate_link_url(AboutDialog& about_dialog, const Glib::ustring& link);
   */
  typedef sigc::slot<void, AboutDialog& /* about_dialog */, const Glib::ustring& /* link */> SlotActivateLink;

  /** Installs a global callback to be called whenever the user activates an email link in an about dialog.
   * @param slot A function or method to call when an email link is activated.
   */
  static void set_email_hook(const SlotActivateLink& slot);
  

  /** Installs a global callback to be called whenever the user activates a URL link in an about dialog.
   * @param slot A function or method to call when a URL link is activated.
   */
  static void set_url_hook(const SlotActivateLink& slot);
  

//TODO: Deprecate this, because it conflicts with the property in GtkWidget, which will be deprecated in GTK+ 2.12.
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The name of the program. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_name() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The name of the program. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_name() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The version of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_version() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The version of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_version() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Copyright information for the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_copyright() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Copyright information for the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_copyright() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Comments about the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_comments() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Comments about the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_comments() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The URL for the link to the website of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_website() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The URL for the link to the website of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_website() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The label for the link to the website of the program. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_website_label() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The label for the link to the website of the program. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_website_label() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The license of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_license() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The license of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_license() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** List of authors of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::StringArrayHandle> property_authors() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** List of authors of the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::StringArrayHandle> property_authors() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** List of people documenting the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::StringArrayHandle> property_documenters() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** List of people documenting the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::StringArrayHandle> property_documenters() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Credits to the translators. This string should be marked as translatable.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::StringArrayHandle> property_translator_credits() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Credits to the translators. This string should be marked as translatable.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::StringArrayHandle> property_translator_credits() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** List of people who have contributed artwork to the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::StringArrayHandle> property_artists() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** List of people who have contributed artwork to the program.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::StringArrayHandle> property_artists() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** A logo for the about box. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy< Glib::RefPtr<Gdk::Pixbuf> > property_logo() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** A logo for the about box. If this is not set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Gdk::Pixbuf> > property_logo() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** A named icon to use as the logo for the about box.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_logo_icon_name() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** A named icon to use as the logo for the about box.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_logo_icon_name() const;
#endif //#GLIBMM_PROPERTIES_ENABLED
  
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether to wrap the license text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
//  Glib::PropertyProxy<bool> property_wrap_license() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether to wrap the license text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
//  Glib::PropertyProxy_ReadOnly<bool> property_wrap_license() const;
#endif //#GLIBMM_PROPERTIES_ENABLED
  

};

} // namespace Gtk


namespace Glib
{
  /** @relates Gtk::AboutDialog
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::AboutDialog* wrap(GtkAboutDialog* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_ABOUTDIALOG_H */

