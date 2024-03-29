/* Copyright (c) 2001, 2004, Oracle Corporation.  All rights reserved.  */
/*
   NAME
     occidml.cpp - Basic DML Operations demo

   DESCRIPTION
     To exhibit the insertion, selection, updating and deletion of
     a row using OCCI interface

   MODIFIED   (MM/DD/YY)
   sudsrini   07/23/04 - Copyright Info
   idcqe      03/05/01 - Creation

*/

#include <iostream>
#include <occi.h>
using namespace oracle::occi;
using namespace std;

class  occidml
{
  private:

  Environment *env;
  Connection *conn;
  Statement *stmt;
  public:

  occidml (string user, string passwd, string db)
  {
    try
    {
    	env = Environment::createEnvironment (Environment::DEFAULT);
    	conn = env->createConnection (user, passwd, db);
    }
    catch(SQLException &sqlExcp)
    {
	cerr <<sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
    }
    catch (exception &excp)
    {
	cerr << excp.what() << endl;
    }
  }

  ~occidml ()
  {
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);
  }


void createTable()
{
	stmt = conn->createStatement();
	string mySQL1 = "CREATE TABLE author_tab (author_id NUMBER, author_name VARCHAR2(25))";
	try
	{
		stmt->executeUpdate(mySQL1);
	}
	catch(SQLException e)
	{
		cerr << "table exits" << endl << "drop table..." << endl;
		stmt->executeUpdate("drop table author_tab");
		cerr << "drop table success" << endl;
		cout << "create table again..." << endl;
		stmt->executeUpdate(mySQL1);
	}
	string mySQL2 = "CREATE TABLE elements (element_name VARCHAR2(25),molar_volume BINARY_FLOAT,atomic_weight BINARY_DOUBLE)";
	try
	{
		stmt->executeUpdate(mySQL2);
	}
	catch(SQLException e)
	{
		cerr << "table exits" << endl << "drop table..." << endl;
                stmt->executeUpdate("drop table elements");
                cerr << "drop table success" << endl;
                cout << "create table again..." << endl;
                stmt->executeUpdate(mySQL2);
	}
}

  /**
   * Insertion of a row with dynamic binding, PreparedStatement functionality.
   */
  void insertBind (int c1, string c2)
  {
    string sqlStmt = "INSERT INTO author_tab VALUES (:x, :y)";
    stmt=conn->createStatement (sqlStmt);
    try{
    stmt->setInt (1, c1);
    stmt->setString (2, c2);
    stmt->executeUpdate ();
    cout << "insert - Success" << endl;
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for insertBind"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    conn->terminateStatement (stmt);
  }

  /**
   * Inserting a row into the table.
   */
  void insertRow ()
  {
    string sqlStmt = "INSERT INTO author_tab VALUES (111, 'ASHOK')";
    stmt = conn->createStatement (sqlStmt);
    try{
    stmt->executeUpdate ();
    cout << "insert - Success" << endl;
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for insertRow"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    conn->terminateStatement (stmt);
  }

  /**
   * updating a row
   */
  void updateRow (int c1, string c2)
  {
    string sqlStmt = 
      "UPDATE author_tab SET author_name = :x WHERE author_id = :y";
    stmt = conn->createStatement (sqlStmt);
    try{
    stmt->setString (1, c2);
    stmt->setInt (2, c1);
    stmt->executeUpdate ();
    cout << "update - Success" << endl;
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for updateRow"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    conn->terminateStatement (stmt);
  }


  /**
   * deletion of a row
   */
  void deleteRow (int c1, string c2)
  {
    string sqlStmt = 
      "DELETE FROM author_tab WHERE author_id= :x AND author_name = :y";
    stmt = conn->createStatement (sqlStmt);
    try{
    stmt->setInt (1, c1);
    stmt->setString (2, c2);
    stmt->executeUpdate ();
    cout << "delete - Success" << endl;
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for deleteRow"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    conn->terminateStatement (stmt);
  }

  /**
   * displaying all the rows in the table
   */
  void displayAllRows ()
  {
    string sqlStmt = "SELECT author_id, author_name FROM author_tab \
    order by author_id";
    stmt = conn->createStatement (sqlStmt);
    ResultSet *rset = stmt->executeQuery ();
    try{
    while (rset->next ())
    {
      cout << "author_id: " << rset->getInt (1) << "  author_name: " 
        << rset->getString (2) << endl;
    }
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for displayAllRows"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    stmt->closeResultSet (rset);
    conn->terminateStatement (stmt);
  }

  /**
   * Inserting a row into elements table.
   * Demonstrating the usage of BFloat and BDouble datatypes
   */
  void insertElement (string elm_name, float mvol=0.0, double awt=0.0)
  {
    BFloat mol_vol;
    BDouble at_wt;

    if (!(mvol))
      mol_vol.isNull = TRUE;
    else
      mol_vol.value = mvol;

    if (!(awt))
      at_wt.isNull = TRUE;
    else
      at_wt.value = awt;

    string sqlStmt = "INSERT INTO elements VALUES (:v1, :v2, :v3)";
    stmt = conn->createStatement (sqlStmt);

    try{
    stmt->setString(1, elm_name);
    stmt->setBFloat(2, mol_vol);
    stmt->setBDouble(3, at_wt);
    stmt->executeUpdate ();
    cout << "insertElement - Success" << endl;
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for insertElement"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }
    conn->terminateStatement (stmt);
  }

  /**
   * displaying rows from element table
   */
  void displayElements ()
  {
    string sqlStmt = 
           "SELECT element_name, molar_volume, atomic_weight FROM elements \
    order by element_name";
    stmt = conn->createStatement (sqlStmt);
    ResultSet *rset = stmt->executeQuery ();
    try{
    cout.precision(7);
    while (rset->next ())
    {
      string elem_name = rset->getString(1);
      BFloat mol_vol = rset->getBFloat(2);
      BDouble at_wt = rset->getBDouble(3);

      cout << "Element Name: " << elem_name << endl;

      if ( mol_vol.isNull )
        cout << "Molar Volume is NULL" << endl;
      else
        cout << "Molar Volume: " << mol_vol.value << " cm3 mol-1" << endl;

      if ( at_wt.isNull )
        cout << "Atomic Weight is NULL" << endl;
      else
        cout << "Atomic Weight: " << at_wt.value << " g/mole" << endl;
    }
    }catch(SQLException ex)
    {
     cout<<"Exception thrown for displayElements"<<endl;
     cout<<"Error number: "<<  ex.getErrorCode() << endl;
     cout<<ex.getMessage() << endl;
    }

    stmt->closeResultSet (rset);
    conn->terminateStatement (stmt);
  }

}; // end of class  occidml


int main (void)
{
  string user = "scott";
  string passwd = "bupt";
  string db = "//192.168.10.183/AMS";

    occidml *demo = new occidml (user, passwd, db);
  
  cout << "Creating table author_tab and elements..." << endl;
  demo->createTable();

  cout << "occidml - Exhibiting simple insert, delete & update operations" 
    << endl;


  cout << "Displaying all records before any operation" << endl;
  demo->displayAllRows ();

  cout << "Inserting a record into the table author_tab " 
    << endl;
  demo->insertRow ();

  cout << "Displaying the records after insert " << endl;
  demo->displayAllRows ();

  cout << "Inserting a records into the table author_tab using dynamic bind"
    << endl;
  demo->insertBind (222, "ANAND");
 
  cout << "Displaying the records after insert using dynamic bind" << endl;
  demo->displayAllRows ();

  cout << "deleting a row with author_id as 222 from author_tab table" << endl;
  demo->deleteRow (222, "ANAND");

  cout << "updating a row with author_id as 444 from author_tab table" << endl;
  demo->updateRow (444, "ADAM");

  cout << "displaying all rows after all the operations" << endl;
  demo->displayAllRows ();

  cout << "inserting radio active element properties" << endl;
  demo->insertElement ("Uranium", 12.572, 238.0289 );
  demo->insertElement ("Plutonium", 12.12, 244.0642 );
  demo->insertElement ("Curium", 18.17, 247.0703 );
  demo->insertElement ("Thorium");
  demo->insertElement ("Radium", 41.337, 226.0254);

  cout << "displaying all radio active element properties" << endl;
  demo->displayElements ();

  delete (demo);
  cout << "occidml - done" << endl;
}
