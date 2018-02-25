# Gmail Inbox based on Google Cloud Platform C++

A program that retrieves messages from Gmail inboxes

## Prerequisites

See the instructions in the root [README](../../../README.md) to build.
In addition, [boost 1.66](http://www.boost.org/users/history/version_1_66_0.html)
is required for the base64 decoding.

Before calling a Google API, you must create a Google Cloud project and enable
billing.

1.  **Create a project in the Google Cloud Platform Console**.
    If you haven't already created a project, create one now. Projects enable
    you to manage all Google Cloud Platform resources for your app, including
    deployment, access control, billing, and services.
    1.  Open the [Cloud Platform Console](https://console.cloud.google.com/).
    2.  In the drop-down menu at the top, select **Create a project**.
    4.  Give your project a name.
    5.  Make a note of the project ID, which might be different from the project
        name. The project ID is used in commands and in configurations.

2.  **Enable billing for your project**.
    If you haven't already enabled billing for your project,
    [enable billing now](https://console.cloud.google.com/project/_/settings).
    Enabling billing allows the application to consume billable resources such
    as running instances and storing data.

## Running Gmail Inbox

Gmail Inbox uses 3-legged authentication. The 3 parties are Google,
you (your Google Cloud Project), and the user.

1.  **Enable APIs.**

    1. Visit the [Google Cloud Console API Manager](
        https://console.cloud.google.com/apis).

    2. Under **G Suite APIs**, click **Gmail API**.

    3. Click **Enable** to enable the Google Gmail API.


2.  **Download credentials**.

    1. Visit the [Google Cloud Console Credentials page](
        https://console.cloud.google.com/apis/credentials).

    2. Click **Create credentials**.

    3. Choose **OAuth client ID**.

    4. For Application type, choose **Other**.

    5. For Name, type **Gmail console application**.

    6. Click **Create**.

    7. The Google Cloud Console will display your client ID and client secret
       in a window.  Click **OK** to close the window.

    8. You should now see `Gmail console application` listed under
       **Oauth 2.0 client IDs**.  Click the down arrow icon to download a
       client secret file.


3.  **Run gmail_inbox**.

    There are 2 sub-commands embedded, namely `retrieve` and `show`.

    ```
    $ bin/gmail_inbox
    Usage:
    1. ./gmail_inbox {retrieve ...}: retrieve messages from Gmail
    2. ./gmail_inbox {show}: show cached messages
    ```

    `retrieve` retrieves messages within a certain period from the authenticated Gmail inbox,
    encrypts them, and stores them into a local file.
    Authentication and Authorization are mandatory via a web browser.
    If a file name is specified to save the credential, the A & A process can be avoided for future runs.

    ```
    $ bin/gmail_inbox retrieve
    Usage:
    ./gmail_inbox retrieve -s secret_path [-c credential_filename] [-f date_from]  [-t date_to]
    -s: specifying the client secret file in json format
    -c: optional, specifying the filename saving the credentials between runs
    -f: optional, specifying the start of the retrieval period in YYYY/MM/DD format
    -t: optional, specifying the end of the retrieval period in YYYY/MM/DD format
    e.g. ./gmail_inbox retrieve -s secret.json -c credential -f 2018/02/01 -t 2018/02/28
    ```

    `show` decrypts the messages saved by the previous `retrieve` run, and prints them onto `stdout`.
