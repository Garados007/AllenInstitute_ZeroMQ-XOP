ZeroMQ XOP
==========

The ZeroMQ XOP allows to interface with Igor Pro over the network using `ZeroMQ
<http://www.zeromq.org>`__ as messaging layer and `JSON
<http://www.json.org>`__ as message format. Reading and writing JSON documents
can be done with the `JSON XOP <https://docs.byte-physics.de/json-xop/>`__.

The XOP provides the following functions:

- :cpp:func:`zeromq_client_connect()`
- :cpp:func:`zeromq_client_recv()`
- :cpp:func:`zeromq_client_send()`
- :cpp:func:`zeromq_handler_start()`
- :cpp:func:`zeromq_handler_stop()`
- :cpp:func:`zeromq_pub_bind`
- :cpp:func:`zeromq_pub_send`
- :cpp:func:`zeromq_server_bind()`
- :cpp:func:`zeromq_server_recv()`
- :cpp:func:`zeromq_server_send()`
- :cpp:func:`zeromq_set()`
- :cpp:func:`zeromq_set_logging_template`
- :cpp:func:`zeromq_stop()`
- :cpp:func:`zeromq_sub_add_filter`
- :cpp:func:`zeromq_sub_connect`
- :cpp:func:`zeromq_sub_recv`
- :cpp:func:`zeromq_sub_remove_filter`

Installation
~~~~~~~~~~~~

Here `XX` denotes your major Igor Pro version, e.g. 8 or 9.

- Download the `ZeroMQ-XOP*.zip` file from the latest `release <https://github.com/AllenInstitute/ZeroMQ-XOP/releases/tag/version>`__.
- Extract it to a folder

Windows
^^^^^^^

- Quit Igor Pro
- Create the following shortcuts in "$HOME\\Documents\\WaveMetrics\\Igor Pro XX User Files"

  - In "Igor Procedures" a shortcut pointing to "procedures"
  - In "Igor Help Files" a shortcut pointing to "help"
  - In "Igor Extensions" a shortcut pointing to "output/win/x86"
  - In "Igor Extensions (64-bit)" a shortcut pointing to "output/win/x64"

- Start Igor Pro

MacOSX
^^^^^^

- Quit Igor Pro
- Unzip the files in "output/mac"
- Create the following symbolic links (symlinks) in "$HOME/Documents/WaveMetrics/Igor Pro XX User Files"

  - In "Igor Procedures" a symlink pointing to "procedures"
  - In "Igor Help Files" a symlink pointing to "help"
  - In "Igor Extensions" a symlink pointing to "output/mac/ZeroMQ"
  - In "Igor Extensions (64-bit)" a symlink pointing to "output/mac/ZeroMQ-64"

- Start Igor Pro

In the following the JSON message format is discussed.

Direction: World -> Igor Pro
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Call Igor Pro functions and return the result
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following table lists all currently supported function parameter and return
types. PRs adding support for new parameter/return types are welcome.

+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|Type                    | by-value Parameter | by-ref Parameter | optional Parameter | Return value | Multiple return values|
+========================+====================+==================+====================+==============+=======================+
|Variable aka double     |         •          |        •         |                    |       •      |           •           |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|Variable/C aka complex  |                    |                  |                    |              |                       |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|Int/int64/uint64/uint   |                    |                  |                    |              |                       |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|String                  |         •          |        •         |                    |       •      |           •           |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|Wave                    |                    |                  |                    |       •      |           •           |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|DFREF                   |         •          |        •         |                    |       •      |           •           |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|FUNCREF                 |                    |                  |                    |              |                       |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+
|STRUCT                  |                    |                  |                    |              |                       |
+------------------------+--------------------+------------------+--------------------+--------------+-----------------------+

The Igor Pro function ``FooBar(string panelTitle, variable index)`` can
be called by sending the following string

.. code-block:: json

    {
      "version"   : 1,
      "messageID" : "my first message",
       "CallFunction" : {
         "name" : "FooBar",
         "params" : [
            "ITC18USB_DEV_0",
            1
         ]
       }
    }

Calling a function without parameters:

.. code-block:: json

    {
      "version" : 1,
       "CallFunction" : {
         "name" : "FooBarWithoutArgs"
       }
    }

Possible responses:

.. code-block:: json

    {
      "errorCode" : {
       "value" : 0
      },
      "messageID" : "my first message",
      "result" : {
        "type" : "variable",
        "value" : 4711
      }
    }

or

.. code-block:: json

    {
      "errorCode" : {
        "value" : 100,
        "msg" : "Function does not exist"
      },
      "messageID" : "my first message",
    }

If the function has pass-by-reference parameters their results are
returned as

.. code-block:: json

    {
      "errorCode": {
          "value": 0
      },
      "passByReference": [
        {
            "type": "variable",
            "value": 4711
        },
        {
            "type": "string",
            "value": "hi there"
        }
      ],
      "result": {
          "type": "variable",
          "value": 42
      }
    }

Functions can also return datafolder references

.. code-block:: json

    {
      "errorCode" : {
       "value" : 0
      },
      "result" : {
        "type"  : "dfref",
        "value" : "root:MIES"
      }
    }

``result.value`` can also be ``free`` or ``null``.

Functions with multiple return values
-------------------------------------

Since Igor Pro 8 functions can return multiple values.

.. code-block:: igorpro

   Function [variable erroCode, string message] FooBarMRS()

      return [42, "Hi there!"]
   End

The function ``FooBarMRS()`` will return the following message:

.. code-block:: json

   {
       "errorCode": {
           "value": 0
       },
       "result": [
           {
               "type": "variable",
               "value": 42
           },
           {
               "type": "string",
               "value": "Hi there!"
           }
       ]
   }

Functions returning waves
-------------------------

Example wave contents (rows are vertical, colums are horizontal)

+---+------+
| 5 | 8    |
+---+------+
| 6 | -inf |
+---+------+
| 7 | 10   |
+---+------+

Waves with standard settings only:

.. code-block:: json

    {
      "errorCode" : {
       "value" : 0
      },
      "result" : {
        "type"  : "wave",
        "value" : {
          "type"     : "NT_FP64",
          "dimSize"  : [3, 2],
          "date"     : {
            "modification" : 10221232
            },
          "data" : {
            "raw" : [5, 6, 7, 8, "-inf", 10]
            }
          }
      }
    }

In case the function returned an invalid wave reference ``$""``:

.. code-block:: json

    {
      "errorCode" : {
       "value" : 0
      },
      "result" : {
        "type"  : "wave",
        "value" : null
      }
    }

The following is an example where all additional settings are present
because they differ from their default values:

.. code-block:: json

    {
      "errorCode" : {
       "value" : 0
      },
      "result" : {
        "type"  : "wave",
        "value" : {
          "type"     : "NT_FP64",
          "date"     : {
            "modification" : 10221232
            },
          "data" : {
            "raw"       : [5, 6, 7, 8, "-inf", 10],
             "unit"      : "m",
             "fullScale" : [5, 10]
            },
          "dimension" : {
            "size"  : [3, 2],
             "delta" : [1, 2.5],
             "offset": [1e5, 3e7],
             "unit"  : ["kHz", "s"],
             "label" : {
               "full"  : [ "some name", "blah" ],
               "each" : [ "..." ]
              }
          },
           "note" : "Hi there I'm a nice wave note and are encoded in \"UTF8\". With fancy things like ï or ß.",
        }
      }
    }

Specification
~~~~~~~~~~~~~

Messages consist of JSON `RFC7158 <https://tools.ietf.org/html/rfc7158>`__
encoded strings with one speciality.  ``NaN``, ``Inf`` and ``-Inf`` are not
supported by JSON, so we encode these non-normal numbers as strings, e.g.
``"NaN"``, ``"Inf"``, ``"+Inf"`` and ``"-Inf"`` (case insensitive).

Sent JSON message
^^^^^^^^^^^^^^^^^

+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+
| Name                | JSON type                | Value                 | Description                                           | Required |
+=====================+==========================+=======================+=======================================================+==========+
| version             | string                   | ``v1``                | global for the complete interface                     | Yes      |
+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+
| operation           | object                   | ``CallFunction``      | operation which should be performed                   | Yes      |
+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+
| CallFunction.name   | string                   | non-empty             | ProcGlobal function without module and or independent |          |
|                     |                          |                       | module specification, i.e. without ``#``.             | Yes      |
+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+
| CallFunction.params | array of strings/numbers | holds strings/numbers | function parameters, conversion will be done eagerly. | No       |
+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+
| messageID           | string                   | user settable         | will be returned in the reply message if present      | No       |
+---------------------+--------------------------+-----------------------+-------------------------------------------------------+----------+

Received JSON message for operation ``CallFunction``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| Name                   | JSON type                | Description                                                                                                        |
+========================+==========================+====================================================================================================================+
| errorCode.value        | number                   | indicates the success/error of the operation, see :cpp:any:`REQ_SUCCESS`                                           |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| errorCode.msg          | string                   | human readable error message, only set if errorCode.value != 0                                                     |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| history                | string                   | Igor Pro history ouputted during function execution, only set if errorCode.value != 0                              |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| return                 | object or array          | function result, will be an array when multiple return value syntax functions are called.                          |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| -> type                | string                   | type of the function result, one of ``string``, ``variable``, ``wave`` or ``dfref``, only for errorCode.value == 0 |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| -> value               | number, string or object | function result, only for errorCode.value == 0                                                                     |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| passByReference        | array of objects         | Changed parameter values for pass-by-reference parameters.                                                         |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| -> type                | string                   | type of the function result, one of ``string``, ``variable`` or ``dfref``                                          |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| -> value               | number or string         | possibly changed input parameters, only for errorCode.value == 0                                                   |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+
| messageID              | string                   | message ID from the sent message. This entry is not present if the sent message did not contain a message id.      |
+------------------------+--------------------------+--------------------------------------------------------------------------------------------------------------------+

Callers are encouraged to **always** check ``errorCode.value`` before processing the rest of the JSON.
Functions returning waves will hold the wave data and metadata as object below ``value``. All strings are UTF8 encoded.
The ``messageID`` allows to correlate responses with requests.

Wave serialization format
~~~~~~~~~~~~~~~~~~~~~~~~~

When the serialization is done as part of the function call reply as shown above, one has to prefix each name with ``value.``.

+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Name                 | JSON type                | Description                                                                                                                                                               |
+======================+==========================+===========================================================================================================================================================================+
| type                 | string                   | wave type; one of NT\_FP32, NT\_FP64, NT\_I8, NT\_I16, NT\_I32, NT\_I64, TEXT\_WAVE\_TYPE, WAVE\_TYPE or DATAFOLDER\_TYPE; or'ed with NT\_UNSIGNED or NT\_CMPLX if needed |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.size       | array of 1 to 4 numbers  | either "32-bit unsigned int" or "64-bit unsigned int" depending on Igor bitness. An empty wave has ``[0]``.                                                               |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.delta      | array of 1 to 4 numbers  | delta  for each dimension                                                                                                                                                 |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.offset     | array of 1 to 4 numbers  | offset  for each dimension                                                                                                                                                |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.label.full | array of 1 to 4 stringss | dimension labels for the full dimensions                                                                                                                                  |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.label.each | array of strings         | dimension labels for each row/column/layer/chunk, colum-major format as ``result.data.raw``                                                                               |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| dimension.unit       | array of 1 to 4 strings  | arbitrary strings denoting the unit for each dimension. The contents are most likely SI with prefix, but this is not guaranteed.                                          |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| date.modification    | number                   | time of last modification in seconds since unix epoch in UTC. 0 for free waves.                                                                                           |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| data.raw             | array of numbers/strings | column-major format, read it with ``np.array([5, 6, 7, 8, "-inf", 10]).reshape(3, 2, order='F')`` using Python.                                                           |
|                      |                          | For complex waves ``raw`` has two properties ``real`` and ``imag`` both holding arrays. For wave reference waves this holds a new instance of a wave object or null.      |
|                      |                          | For type equal ``WAVE_TYPE`` this holds an array with waves. Each array entry is an object with again ```` entries.                                                       |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| data.unit            | string                   | arbitrary strings denoting the unit. The contents are most likely SI with prefix, but this is not guaranteed.                                                             |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| data.fullScale       | array of 2 numbers       | min and max of the data (non-authorative)                                                                                                                                 |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| note                 | string                   | wave note                                                                                                                                                                 |
+----------------------+--------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

Direction: Igor Pro -> World
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The XOP implements Publisher/Subscriber sockets. This allows applications outside of Igor Pro to be notified about events
in Igor Pro. The implementation uses plain PUB/SUB sockets, but XPUB/XSUB sockets should be compatible as well.

The published messages will be a multipart message with two frames, see also the official `documentation
<https://zguide.zeromq.org/docs/chapter2/#Pub-Sub-Message-Envelopes>`__:

.. code-block:: sh

   Frame 1: Filter
   Frame 2: Data

where ``Filter`` is the message type and ``Data`` the payload. No serialization format of ``Data`` is enforced, but users are
encouraged to use standard serialization formats like JSON.

Subscriber sockets will only receive messages from their subscribed filters. By default there are no subscriptions to
any filters.

One publisher message is sent out every five seconds, this is the "heartbeat" message with no data.

Users are encouraged to offer a list of available message filters via server/client sockets and calling a pre-agreed
function which returns a text wave.

Compilation instructions
^^^^^^^^^^^^^^^^^^^^^^^^

Required additional software:

- (Windows only) Visual Studio 2019
- (MacOSX only) Xcode
- `CMake <https://cmake.org>`__ version 3.15 or later
- `XOPSupport Toolkit 8 <https://www.wavemetrics.com/products/xoptoolkit/xoptoolkit.htm>`__
- `Igor Unit Testing Framework <https://github.com/byte-physics/igor-unit-testing-framework>`__

Building and installing the ZeroMQ.xop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

See also ``.gitlab.ci.yml`` for up-do-date build instructions.

.. code-block:: sh

   # Windows
   # {
   # Install cmake from www.cmake.org
   # Install Visual Studio 2019 Community
   # Open a Visual Studio 2019 command prompt
   cd Packages/ZeroMQ/src
   md build build-64
   cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE_BUILD_TYPE=Release ..
   cmake --build . --config Release --target install
   cd ..
   cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release ..
   cmake --build . --config Release --target install
   # }

   # MacOSX
   # {
   cmake -G Xcode -DCMAKE_BUILD_TYPE=Release ..
   cmake --build . --config Release --target install
   # }

Running the test suite
~~~~~~~~~~~~~~~~~~~~~~

- Clone the `Igor Unit Testing Framework <https://github.com/byte-physics/igor-unit-testing-framework>`_.
- Create in "Igor Procedures" a shortcut pointing to the "procedures" directory of that repository.
- Open Packages/ZeroMQ/tests/RunTests.pxp
- Execute in Igor ``run()``
- The test suite always passes *without* errors

ZeroMQ XOP implementation details
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The XOP uses the ``Dealer`` (called Client in the XOP interface), ``Router`` (called Server in the XOP interface) and
``Publisher``/``Subscriber`` socket types.

The default socket options are:

- ``ZMQ_LINGER``           = ``0``
- ``ZMQ_SNDTIMEO``         = ``0``
- ``ZMQ_RCVTIMEO``         = ``0``
- ``ZMQ_ROUTER_MANDATORY`` = ``1`` (``Router`` only)
- ``ZMQ_MAXMSGSIZE``       = ``1024`` (in bytes, ``Router`` only)
- ``ZMQ_IDENTITY``         = ``zeromq xop: dealer`` (``Dealer`` only)

The ``Router``/Server expects three frames (identity, empty, payload) and the
``Dealer``/Client expects two frames (empty, payload) when sending/receiving
messages. This format is used to be compatible with REP/REQ sockets.

The ``Publisher``/``Subscriber`` send/expect two frames (filter, payload). This is done so that there is no ambiguity
between filter and payload. The payload can be empty.

The passed function in the JSON message is currently always executed in the
main thread during ``IDLE`` events. ``IDLE`` events are generated by Igor Pro
only when no functions are running. In case you want to execute a function
during the time when functions are running the operation ``DoXOPIdle`` allows
to force an ``IDLE`` event.

Logging
~~~~~~~

The XOP allows to log all incoming and outgoing messages to disk. This can be enabled via ``zeromq_set``. The log format
is `JSONL <https://jsonlines.org>`__. Additional static entries can be added to every line via
``zeromq_set_logging_template`` which allows to set a new template JSON text.

The location of the log file on Windows is ``C:\Users\$user\AppData\Roaming\WaveMetrics\Igor Pro $version\Packages\ZeroMQ\Log.jsonl``.
